/*
 * Name: MegaMenuC
 * Date: 2022/06/03
 * Author: Max Base
 * Repository: https://github.com/BaseMax/MegaMenuC
 */

#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tree_value_t;

struct tree_t {
    int size;
    struct tree_value_t **items;
};
struct tree_value_t {
    char* id;
    char* name;
    struct tree_t* children;
};

void db_error_exit(MYSQL *con)
{
    fprintf(stderr, "Sorry, Error: %s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void display(struct tree_t* tree, int space)
{
    for (int i = 0; i < tree->size; i++) {
        struct tree_value_t* item = tree->items[i];

        if (space > 0) {
            for (int j = 0; j < space; j++) printf(" ");
        }
        printf("- %s\n", item->name);

        // recursive call
        display(item->children, space + 5);
    }
}

struct tree_t* menu(MYSQL *con, int parent_id)
{
    struct tree_t *items = (struct tree_t*)malloc(sizeof(struct tree_t));
    items->size = 0;
    const int MAX_CHILD = 124;
    items->items = (struct tree_value_t**)malloc(MAX_CHILD * sizeof(struct tree_value_t*));

    char *sql = malloc(sizeof(char) * 1024);
    char *sql_prefix = "SELECT `menu_item`.* FROM `menu` INNER JOIN `menu_item` ON `menu_item`.`id` = `menu`.`menu_id` WHERE `menu`.`parent_id`";
    if (parent_id == 0) // root
        sprintf(sql, "%s IS NULL", sql_prefix);
    else
        sprintf(sql, "%s = %d", sql_prefix, parent_id);


    if (mysql_query(con, sql)) db_error_exit(con);
    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) db_error_exit(con);
    // int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        struct tree_value_t *item = (struct tree_value_t*)malloc(sizeof(struct tree_value_t));
        item->id = row[0];
        item->name = malloc(sizeof(char) * (strlen(row[1]) + 1));
        strcpy(item->name, row[1]);
        item->children = menu(con, atoi(row[0]));

        items->items[items->size++] = item;
    }

    mysql_free_result(result);

    return items;
}

int main(int argc, char **argv)
{
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // NOTE: You need to put your own username, password, and database name here
    if (mysql_real_connect(con, "localhost", "root", "*************", "*************", 0, NULL, 0) == NULL) db_error_exit(con);

    struct tree_t *tree = menu(con, 0); // 0 mean main menu items without parent
    display(tree, 0); // 0 mean no spacing from left side

    mysql_close(con);

    exit(0);
}
