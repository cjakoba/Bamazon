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
    char username[15];
    scanf("%s", username);

    // Determine and set user mode beforehand
    int mode = 0;
    if (strcmp(username, "bamazon") == 0) {
        mode = 1;
    } else if (strcmp(username, "shopper") == 0) {
    } else {
        fprintf(stderr, "Invalid user!");
        exit(-1);
    }

    //bamazon user
    int b = 1;
    while (b) {
        char sel[150];

        printf("Welcome to Bamazon!\n");
        printf("Please choose from the following commands: \n");

        // Print this only for the bamazon user.
        if (mode) {
            printf("add itemnum itemcategory itemname size quantity cost onsale\n");
            printf("delete itemnum\n");
            printf("updatecost itemnum cost\n");
            printf("updatequantity itemnum quantity\n");
            printf("save\n");
            printf("quit\n");
        }

        // For all users
        printf("showitems\n");
        printf("showcategory category\n");
        printf("showcategorycost category cost\n");
        printf("showcategorysize category size\n");
        printf("purchase itemnum\n");
        printf("exit\n");

        fflush(stdin);
        fgets(sel, 150, stdin);

        if (strstr(sel, "add") && mode) {
            // Add an item to the database
            int itemnum, onsale, quantity;
            char category[15], name[25], size;
            double cost;

            sscanf(sel, "add %d %s %s %c %d %lf %d", &itemnum, category, name, &size, &quantity, &cost, &onsale);
            add_item(itemnum, category, name, size, quantity, cost, onsale);
        } else if (strstr(sel, "delete") && mode) {
            // Delete an item from the database
            int itemnum;
            sscanf(sel, "%d", &itemnum);

            if (delete_item(itemnum) == 0) {
                fprintf(stderr, "Invalid itemnum!\n");
            }
        } else if (strstr(sel, "updatecost") && mode) {
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
        } else if (strstr(sel, "updatequantity") && mode) {
            // Update the quantity of an item in the database
            int itemnum, quantity;
            sscanf(sel, "updatequantity %d %d", &itemnum, &quantity);

            if (find_item_num(itemnum) == 0) {
                fprintf(stderr, "Invalid itemnum!\n");
            } else {
                item *cur = find_item_num(itemnum);
                cur->quantity = quantity;
            }
        } else if (strstr(sel, "save") && mode) {
            // Save the changes to the database
            write_db("test.txt");
        } else if (strstr(sel, "quit") && mode) {
            // Quit the program without saving changes to the database
            return 0;
        } else if (strstr(sel, "showitems")) {
            // Show all items in the database
            show_items();
        } else if (strstr(sel, "showcategory")) {
            // Show items of a specific category in the database
            char *type;
            sscanf(sel, "showcategory %s", type);

            item *categories[10];
            int cat = get_category(categories, str_to_category(type));
            char print_items[100];
            for (int i = 0; i < cat; i++) {
                sprint_item(print_items, categories[i]);
                printf("%s\n", print_items);
            }
        } else if (strstr(sel, "showcategorycost")) {
            // Show items of a specific category with cost less than a given value
            // Parameters: category, cost
            // Example usage: showcategorycost Clothing 50.0
        } else if (strstr(sel, "showcategorysize")) {
            // Show items of a specific category with a specific size
            // Parameters: category, size
            // Example usage: showcategorysize Clothing L
        } else if (strstr(sel, "purchase")) {
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
}