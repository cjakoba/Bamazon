#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bamazon.h"

// Static variables
// item { int itemnum, enum category category, char size, char name[], char size, in quantity, double cost, int onsale }
// Size of the db array of pointers is 8 bytes * 300 item structures = 2400 bytes
// Size of actual item is 64 bytes as ints and double must be on evenly divisible addresses.
static item *db[MAX_ITEMS];             // Array of MAX_ITEMS pointers to addresses containing an item structure
static int num_items = 0;
static item *purchased[MAX_PURCHASE];
static int purchased_items = 0;

// Takes in a string filename to open for reading into internal database.
// Returns 0 upon successful file opening, -1 for failure.
int read_db(char *filename) {
    char buffer[500];
    char category[50];
    // Safe file handling
    // OPEN - DO - CLOSE: open a file, use file pointer to do file I/O, close the file.
    FILE *in;
    if ((in = fopen(filename, "r")) == NULL) {
        // stderr is a default file descriptor where a process can write error messages.
        fprintf(stderr, "Error: Can't open %s for read operation.\n", filename);
        return -1;
    }

    // Read and store 1 entire line of text at a time until you reach NULL (the end of the file).
    for (int i = 0; fgets(buffer, 75, in); i++, num_items++) {
        db[i] = malloc(sizeof(item));
        sscanf(buffer, "%d %s %s %c %d %lf %d", &db[i]->itemnum, category, db[i]->name, &db[i]->size, &db[i]->quantity, &db[i]->cost, &db[i]->onsale);

        // Add enumeration to item's internal db via case insensitive string comparison.
        // Note: strcmpi is not part of POSIX
        if (strcmp(category, "clothes") == 0) {
            db[i]->category = 0;
        } else if (strcmp(category, "electronics") == 0) {
            db[i]->category = 1;
        } else if (strcmp(category, "tools") == 0) {
            db[i]->category = 2;
        } else if (strcmp(category, "toys") == 0) {
            db[i]->category = 3;
        }
    }
}

// Takes in a string filename for overwriting from internal database.
// Returns 0 upon successful file opening, -1 for failure.
int write_db(char *filename) {
    // Safe file handling
    // OPEN - DO - CLOSE: open a file, use file pointer to do file I/O, close the file.
    FILE *out;
    // Produces a new file if it doesn't exist, may remove this code...
    if ((out = fopen(filename, "w+")) == NULL) {
        fprintf(stderr, "Error: Can't open %s for write operation.\n", filename);
        return -1;
    }
    // Prints the items to the file
    for(int i =0; i<num_items; i++){
        fprintf(out, "%d %s %s %c %d %lf %d\n", db[i]->itemnum, category_to_str(db[i]->category), db[i]->name, db[i]->size, db[i]->quantity, db[i]->cost, db[i]->onsale );
    }
    fclose(out);
    return 0;
}

// Prints all items in the internal data structure to the terminal following specific format
void show_items() {
    for (int i = 0; i < num_items; i++) {
        char *s = malloc(100);
        sprint_item(s,db[i]);
        printf("%s\n",s);
        free(s);
    }
}

int sprint_item(char *s, item *c) {
    // Adds the elements of the given item to the given string
    int i = sprintf(s,"%d %s %s %c %d %lf %d", c->itemnum, category_to_str(c->category), c->name, c->size, c->quantity, c->cost, c->onsale);
    //removes hyphens
    for (int j = 0; j < i; j++) {
        if (s[j] == '_') {
            s[j] = ' ';
        }
    }
    return i;
}

item *find_item_num(int itemnum) {
    for (int i = 0; i < num_items; i++) {
        if (db[i]->itemnum == itemnum) {
            return db[i];
        }
    }
    return 0;
}

int find_item_str(item **items, char *s) {
    int itemnum=0;
    int len = strlen(s);
    //loops through items
    for (int i=0;i<num_items;i++ ){
        //only checks if the string is shorter than the name
        if(strlen(db[i]->name)>=len){
        //loop through characters in item name = to the characters in the item name-the length of the string
        for (int j=0;j<=strlen(db[i]->name)-len ;j++ ){
            char ss[len];
            //creates a string that is a substring of the name
            for (int k=0;k<len;k++ ){
                ss[k]=db[i]->name[j+k];
            }
            //compares the ss of the name to the passed in string
            if (strcmp(ss,s)==0){
            *items[itemnum]=*db[i];
            itemnum++;
            break;
            }
        }
        }
    }
    return itemnum;
}

// bit fields for enums? idea maybe.
item *add_item(int itemnum, char *category, char *name, char size, int quantity, double cost, int onsale) {
    int type = -1;
    char *types[4] = {"clothes", "electronics", "tools", "toys"};

    for (int i = 0; i < 4; i++) {
        if (strcmp(category, types[i]) == 0) {
            type = i;
        }
    }

    // Incorrect category
    if (type == -1) {
        fprintf(stderr, "Invalid category!\n");
        return 0;
    }

    // When an item with itemnum already exists in the database, just update it
    item *selected = find_item_num(itemnum);
    if (selected != NULL) {

        selected->itemnum = itemnum;
        selected->category = str_to_category(category);
        strcpy(selected->name, name);
        selected->size = size;
        selected->quantity = quantity;
        selected->cost = cost;
        selected->onsale = onsale;
        return selected;
    }

    // Create a new item if it doesn't already exist.
    item *new_item = malloc(sizeof(item));

    // Add to database
    db[num_items++] = new_item;

    // Update its values
    new_item->itemnum = itemnum;
    new_item->category = str_to_category(category);
    strcpy(new_item->name, name);
    new_item->size = size;
    new_item->quantity = quantity;
    new_item->cost = cost;
    new_item->onsale = onsale;
    return new_item;
}

// Selects all items matching a specific category and fills in the item items array.
// Returns the number of items placed in the array.
int get_category(item **items, category c) {
    return get_category_cost(items, c, -1.0); // Calling with cost invalid (-1) just filters by category c.
}

int get_category_size(item **items, category c, char size) {
    int count = 0;
    for (int i = 0; i < num_items; i++) {
        // Filter by category and size
        if (db[i]->category == c && db[i]->size == size) {
            items[count++] = db[i];
        }
    }
    return count;
}

// Selects all items matching a specific category, costing less than cost, and fills in the item items array.
// Returns integer value of number of elements in item array.
int get_category_cost(item **items, category c, double cost) {
    int count = 0;
    for (int i = 0; i < num_items; i++) {
        // Filter by category.
        if (db[i]->category == c) {
            // Filter by cost if cost isn't invalid (-1).
            if (db[i]->cost < cost && cost != -1.0) {
                items[count++] = db[i];
            } else if (cost == -1.0){
                // Invalid cost sorts by just category.
                items[count++] = db[i];
            }
        }
    }
    return count;
}
//removes one from inventory, and adds item to purchased items
item *purchase_item(int itemnum) {
    item *cur = find_item_num(itemnum);
    if(cur != 0){
        if(cur->quantity <= 0){
            return 0;
        }
        cur->quantity--;
        purchased[purchased_items++] = cur;
        return cur;
    }
    return 0;
}
//prints item to receipt, sets purchased items to 0
int checkout(char **receipt) {
    int count = 0;
    for (int i = 0; i < purchased_items; i++) {
        sprint_item(receipt[i], purchased[i]);
    }
    count = purchased_items;
    purchased_items = 0;
    return count;
}

// Returns the selected item and deletes the item from the internal db, returning 0 upon failure.
item *delete_item(int itemnum) {
    item *selection;
    int position = 0;
    // Gets the position of the item matching the parameter.
    while (position < num_items) {
        if (db[position]->itemnum == itemnum) {
            // Store the address of the item for returning and update number of items in db.
            selection = db[position];
            num_items--;

            // When selected shift to the left the rest of the items in the internal db to fill gap in.
            while (position < num_items) {
                db[position] = db[position + 1];
                position++;
            }
            return selection;
        }
        position++;
    }
    return 0;
}

// Converts the enum category type returning its string representation.
char *category_to_str(category c) {
    // Use enum treated as int to select from array of strings representing those enums, allocate memory for returning.
    char *types[4] = {"clothes", "electronics", "tools", "toys"};
    return strcpy(malloc(strlen(types[c]) + 1), types[c]);
}

category str_to_category(char *s) {
    if (strcmp(s, "clothes") == 0) {
        return 0;
    } else if (strcmp(s, "electronics") == 0) {
        return 1;
    } else if (strcmp(s, "tools") == 0) {
        return 2;
    } else if (strcmp(s, "toys") == 0) {
        return 3;
    } else {
        return -1;
    }
}

