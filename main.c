#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bamazon.h"

int main(int argc, char **argv) {
    if (read_db("bamdata.txt")==0){ 
    printf("Enter user name:");
    char s[20];
    scanf("%s",s);
    //bamazon user
    if (strcmp(s,"bamazon")==0){
    int b=1;
    while(b){
    printf("Welcome to Bamazon!\nPlease choose from the following commands:\nadd itemnum itemcategory itemname size quantity cost onsale\ndelete itemnum\nupdatecost itemnum cost\nupdatequantity itemnum quantity\nsave\nquit\nshowitems\nshowcategory category\nshowcategorycost category cost\nshowcategorysize category size\npurchase itemnum\nexit\n");
    char sel[20];
    scanf("%s",sel);
    if(strcmp(sel,"add")==0) {
        // Add an item to the database
    int itemnum, onsale, quantity;
    char category[15],name[25],size;
    double cost;
    scanf("%d %s %s %c %d %lf %d",&itemnum, category, name, &size, &quantity, &cost, &onsale);
    add_item(itemnum, category, name, size, quantity, cost, onsale);
    }else if(strcmp(sel,"delete")==0) {
        // Delete an item from the database
        int itemnum;
        scanf("%d", &itemnum);
        if(delete_item(itemnum)==0){printf("Invalid itemnum!\n");}    
    }else if(strcmp(sel,"updatecost")==0) {
        // Update the cost of an item in the database
        int itemnum;
        double cost; 
        scanf("%d %lf", &itemnum, &cost);
        if (find_item_num(itemnum)==0){
        printf("Invalid itemnum!\n");
        }else{
        item *cur= find_item_num(itemnum);
        cur->cost=cost;
        }
    }else if(strcmp(sel,"updatequantity")==0) {
        // Update the quantity of an item in the database
        int itemnum,quantity; 
        scanf("%d %d", &itemnum, &quantity);
        if (find_item_num(itemnum)==0){ 
        printf("Invalid itemnum!/n");
        }else{
          item *cur= find_item_num(itemnum);
          cur->quantity=quantity;
        }
    }else if(strcmp(sel,"save")==0) {
        // Save the changes to the database
        write_db("test.txt");
    }else if(strcmp(sel,"quit")==0) {
        // Quit the program without saving changes to the database
        b=0;
    }else if(strcmp(sel,"showitems")==0) {
        // Show all items in the database
        show_items();
    }else if(strcmp(sel,"showcategory")==0) {
        // Show items of a specific category in the database
        
    }else if(strcmp(sel,"showcategorycost")==0) {
        // Show items of a specific category with cost less than a given value
        // Parameters: category, cost
        // Example usage: showcategorycost Clothing 50.0
    }else if(strcmp(sel,"showcategorysize")==0) {
        // Show items of a specific category with a specific size
        // Parameters: category, size
        // Example usage: showcategorysize Clothing L
    }else if(strcmp(sel,"purchase")==0) {
        // Purchase an item from the database
        int itemnum;
        scanf("%d", &itemnum);
        purchase_item(itemnum);
        char **receipt=malloc(40);
        checkout(receipt);
    }else if(strcmp(sel,"exit")==0) {
        // Exit the program and save changes to the database
        write_db("test.txt");
        b=0;
        
    }else{// Invalid command
        printf("Invalid command!\n");
    // TODO: check to see if user input is even there from terminal, input would be like ./bamazon bamdata.txt
    // Where bamdata.txt is considered the 1th argument (argv[1]).
    // if not there, terminate program with error asking for a filename
    //read_db(argv[1]);
    //add_item(10, "electronics", "test", 'm', 99, 99.99, 99);
    //add_item(100, "electronics", "test", 'm', 99, 99.99, 99);
    //show_items();
    //return 0;
}
}
}
//TODO:copy shopper only code here when complete 
}else{
printf("Invalid user!");
}
return 0;
}

