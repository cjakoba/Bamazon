# Bamazon

## Ted
- [ ] main (int argv, char ** argc)
- [ ] int write_db(char *filename);
- [ ] int sprint_item(char *s, item *c);
- [ ] int find_item_str(item **items, char *s);
- [ ] item *update_item(int itemnum, category category, char *name, char size, int quantity, double cost, int onsale);
- [ ] int get_category_size(item **items, category c, char size);
- [ ] item *purchase_item(int itemnum);
- [ ] int checkout(char **receipt);
- [ ] category str_to_category(char *s);

## Christian
- [X] int read_db(char *filename);
- [ ] void show_items();
- [ ] item *find_item_num(int itemnum);
- [ ] item *add_item(int itemnum, char *category, char *name, char size, int quantity, double cost, int onsale);
- [ ] int get_category(item **items, category c);
- [ ] int get_category_cost(item **items, category c, double cost);
- [X] item *delete_item(int itemnum);
- [X] char *category_to_str(category c);
