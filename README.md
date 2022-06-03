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
