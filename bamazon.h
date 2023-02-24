#define MAX_ITEMS 300
#define MAX_ITEMS_CHARS 32
#define MAX_PURCHASE 10

typedef enum {
	clothes, electronics, tools, toys
} category;

typedef struct {
	int itemnum;
	category category;
	char name[MAX_ITEMS_CHARS];
	char size;
	int quantity;
	double cost;
	int onsale;
} item;

// Function declarations (function prototypes or function signatures)
int read_db(char *filename);
int write_db(char *filename);
void show_items();
int sprint_item(char *s, item *c);
item *find_item_num(int itemnum);
int find_item_str(item **items, char *s);
item *add_item(int itemnum, char *category, char *name, char size, int quantity, double cost, int onsale);
int get_category(item **items, category c);
int get_category_size(item **items, category c, char size);
int get_category_cost(item **items, category c, double cost);
item *purchase_item(int itemnum);
item *delete_item(int itemnum);
int checkout(char **receipt);
char *category_to_str(category c);
category str_to_category(char *s);
