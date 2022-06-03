#include <mysql.h>
#include <stdio.h>
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

int main(int argc, char **argv)
{
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    if (mysql_real_connect(con, "localhost", "root", "$$$$Erfan01$$$$", "kambiz", 0, NULL, 0) == NULL) db_error_exit(con);

    struct tree_t *tree = menu(con, 0); // 0 mean main menu items without parent
    display(tree, 0); // 0 mean no spacing from left side

    mysql_close(con);

    exit(0);
}
