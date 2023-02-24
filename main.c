#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bamazon.h"

int main(int argc, char **argv) {
    int try_reading = read_db(argv[1]);

    // Exit early file the file does not exist.
    if (try_reading == -1) {
        fprintf(stderr, "File not found!");
        exit(-1);
    }

    printf("Enter user name: ");
    char s[15];
    scanf("%s", s);

    //bamazon user
    if (strcmp(s, "bamazon") == 0) {
        int b = 1;
        while (b) {
            char sel[150];
            printf("Welcome to Bamazon!\nPlease choose from the following commands:\nadd itemnum itemcategory itemname size quantity cost onsale\ndelete itemnum\nupdatecost itemnum cost\nupdatequantity itemnum quantity\nsave\nquit\nshowitems\nshowcategory category\nshowcategorycost category cost\nshowcategorysize category size\npurchase itemnum\nexit\n");
            fflush(stdin);
            fgets(sel, 150, stdin);

            if (strstr(sel, "add")) {
                // Add an item to the database
                int itemnum, onsale, quantity;
                char category[15], name[25], size;
                double cost;

                sscanf(sel, "add %d %s %s %c %d %lf %d", &itemnum, category, name, &size, &quantity, &cost, &onsale);
                add_item(itemnum, category, name, size, quantity, cost, onsale);
            } else if (strstr(sel, "delete")) {
                // Delete an item from the database
                int itemnum;
                sscanf(sel, "%d", &itemnum);

                if (delete_item(itemnum) == 0) {
                    fprintf(stderr, "Invalid itemnum!\n");
                }
            } else if (strstr(sel, "updatecost")) {
                // Update the cost of an item in the database
                int itemnum;
                double cost;
                sscanf(sel, "updatecost %d %lf", &itemnum, &cost);

                if (find_item_num(itemnum) == NULL) {
                    fprintf(stderr, "Invalid itemnum!\n");
                } else {
                    item *cur = find_item_num(itemnum);
                    cur->cost = cost;
                }
            } else if (strcmp(sel, "updatequantity") == 0) {
                // Update the quantity of an item in the database
                int itemnum, quantity;
                scanf("%d %d", &itemnum, &quantity);
                if (find_item_num(itemnum) == 0) {
                    printf("Invalid itemnum!/n");
                } else {
                    item *cur = find_item_num(itemnum);
                    cur->quantity = quantity;
                }
            } else if (strcmp(sel, "save") == 0) {
                // Save the changes to the database
                write_db("test.txt");
            } else if (strstr(sel, "quit")) {
                // Quit the program without saving changes to the database
                return 0;
            } else if (strstr(sel, "showitems")) {
                // Show all items in the database
                show_items();
            } else if (strcmp(sel, "showcategory") == 0) {
                // Show items of a specific category in the database

            } else if (strcmp(sel, "showcategorycost") == 0) {
                // Show items of a specific category with cost less than a given value
                // Parameters: category, cost
                // Example usage: showcategorycost Clothing 50.0
            } else if (strcmp(sel, "showcategorysize") == 0) {
                // Show items of a specific category with a specific size
                // Parameters: category, size
                // Example usage: showcategorysize Clothing L
            } else if (strcmp(sel, "purchase") == 0) {
                // Purchase an item from the database
                int itemnum;
                scanf("%d", &itemnum);
                char *receipt[150];
                checkout(receipt);
            } else if (strstr(sel, "exit")) {
                // Exit the program and save changes to the database
                write_db("test.txt");
                return 0;
            } else {
                fprintf(stderr, "Invalid command!\n");
            }
        }
    } else if (strcmp(s, "shopper") == 0) {
        // Shopper commands here.
        printf("Shopper\n");
        return 0;
    }

    // Otherwise user input is invalid
    printf("Invalid user!\n");
    return 0;
}

