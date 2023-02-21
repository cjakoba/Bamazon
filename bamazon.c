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
        if (strcmpi(category, "clothes") == 0) {
            db[i]->category = 0;
        } else if (strcmpi(category, "electronics") == 0) {
            db[i]->category = 1;
        } else if (strcmpi(category, "tools") == 0) {
            db[i]->category = 2;
        } else if (strcmpi(category, "toys") == 0) {
            db[i]->category = 3;
        }

        // Removal of underscores from names
        for (int j = 0; j < MAX_ITEMS_CHARS; j++) {
            if (db[i]->name[j] == '_') {
                db[i]->name[j] = ' ';
            }
        }

        // Final result of internal database, to be removed before turning project in.
        printf("%d %d %s %c %d %lf %d\n", db[i]->itemnum, db[i]->category, db[i]->name, db[i]->size, db[i]->quantity, db[i]->cost, db[i]->onsale);
    }
    printf("Number of items: %d\n", num_items);

    fclose(in);
    return 0;
}

// Takes in a string filename for overwriting from internal database.
// Returns 0 upon successful file opening, -1 for failure.
int write_db(char *filename) {
    // Safe file handling
    // OPEN - DO - CLOSE: open a file, use file pointer to do file I/O, close the file.
    FILE *out;
    // Produces a new file if it doesn't exist, may remove this code...
    if ((out = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "Error: Can't open %s for write operation.\n", filename);
        return -1;
    }

    // TODO: write db into file. Names with spaces to have underscores placed. Category to switch from enum to string.

    fclose(out);
    return 0;
}

void show_items() {

}

int sprint_item(char *s, item *c) {
    return 0;
}

// Commented out to test other functions
//item *find_item_num(int itemnum) {
//    return NULL;
//}

int find_item_str(item **items, char *s) {
    return 0;
}

//item *add_item(int itemnum, char *category, char *name, char size, int quantity, double cost, int onsale) {
//    return NULL;
//}

//item *update_item(int itemnum, category category, char *name, char size, double cost, int onsale) {
//    return NULL;
//}

int get_category(item **items, category c) {
    return 0;
}

int get_category_size(item **items, category c, char size) {
    return 0;
}

int get_category_cost(item **items, category c, double cost) {
    return 0;
}

//item *purchase_item(int itemnum) {
//    return NULL;
//}

int checkout(char **receipt) {
    return 0;
}

char *category_to_str(category c) {
    return NULL;
}

category str_to_category(char *s) {
    return electronics;
}

