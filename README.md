# Mega Menu C

**MegaMenuC** is a simple menu system for C that allows you to recursively get menu items and its submenus.

## Using

```sh
$ gcc menu.c -o menu -I/usr/include/mysql -lmysqlclient
$ ./menu
```

### Tree

```
- Personal cabinet
- News
     - Sub Test 1
          - Sub Test 2
- Sitemap
     - Sub Test 1
          - Sub Test 2
- Information
     - Sub Test 1
          - Sub Test 2
- Contacts
- System
     - Official site
     - Supporting forum
```

### Test Table Data

**Menu:**

| ID | Menu ID | Parent ID|
|----|---------|----------|
| 1 | 1 | NULL |
| 2 | 2 | NULL |
| 3 | 3 | NULL |
| 4 | 4 | NULL |
| 5 | 5 | NULL |
| 6 | 6 | NULL |
| 7 | 7 | 6 |
| 8 | 8 | 6 |
| 9 | 9 | 2 |
| 10 | 9 | 3 |
| 11 | 9 | 4 |
| 12 | 10 | 9 |

**Menu Item:**

| ID | Name |
|----|------|
| 1 | Personal cabinet |
| 2 | News |
| 3 | Sitemap |
| 4 | Information |
| 5 | Contacts |
| 6 | System |
| 7 | Official site |
| 8 | Supporting forum |
| 9 | Sub Test 1 |
| 10, | Sub Test 2 |

### Database Structure

```sql
CREATE TABLE `menu` (
  `id` int(20) NOT NULL,
  `menu_id` int(20) NOT NULL,
  `parent_id` int(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE `menu_item` (
  `id` int(20) NOT NULL,
  `name` varchar(54) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

© Copyright 2022, Max Base
