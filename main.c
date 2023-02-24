#include <stdio.h>
#include <string.h>
#include "bamazon.h"

int main(int argc, char **argv) {
    if (read_db("bamdata.txt")==0){ 
    printf("Enter user name:");
    char s[20];
    scanf("%s",s);

    if (strcmp(s,"bamazon")==0){
    int b=1;
    while(b){
    printf("Options");
    int sel;
    scanf("%d",&sel);
    switch(sel) {
    case 1:
        // Add an item to the database
        // Parameters: itemnum, category, itemname, size, quantity, cost, onsale
        // Example usage: additemnumtemcategoryitemnamesizequantitycostonsale 123 Clothing Shirt L 10 29.99 1
        
        break;
    case 2:
        // Delete an item from the database
        // Parameters: itemnum
        // Example usage: deleteitemnum 123
        break;
    case 3:
        // Update the cost of an item in the database
        // Parameters: itemnum, cost
        // Example usage: updatecostitemnumcost 123 19.99
        break;
    case 4:
        // Update the quantity of an item in the database
        // Parameters: itemnum, quantity
        // Example usage: updatequantity 123 5
        break;
    case 5:
        // Save the changes to the database
        write_db("test.txt");
        break;
    case 6:
        // Quit the program without saving changes to the database
        b=0;
        break;
    case 7:
        // Show all items in the database
        show_items();
        break;
    case 8:
        // Show items of a specific category in the database
        // Parameters: category
        // Example usage: showcategory Clothing
        break;
    case 9:
        // Show items of a specific category with cost less than a given value
        // Parameters: category, cost
        // Example usage: showcategorycost Clothing 50.0
        break;
    case 10:
        // Show items of a specific category with a specific size
        // Parameters: category, size
        // Example usage: showcategorysize Clothing L
        break;
    case 11:
        // Purchase an item from the database
        // Parameters: itemnum
        // Example usage: purchase 123
        break;
    case 12:
        // Exit the program and save changes to the database
        write_db("test.txt");
        b=0;
        break;
    default:
        // Invalid command
        printf("Invalid command!\n");
        break;
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

else if(strcmp(s,"shopper")==0){
//TODO:copy shopper only code here when complete 
}else{
printf("Invalid user!");
}
}
return 0;
}

