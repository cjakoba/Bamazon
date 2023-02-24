#include <stdio.h>
#include "bamazon.h"

int main(int argc, char **argv) {
    // TODO: check to see if user input is even there from terminal, input would be like ./bamazon bamdata.txt
    // Where bamdata.txt is considered the 1th argument (argv[1]).
    // if not there, terminate program with error asking for a filename
    read_db(argv[1]);
    add_item(10, "electronics", "test", 'm', 99, 99.99, 99);
    add_item(100, "electronics", "test", 'm', 99, 99.99, 99);
    show_items();
    return 0;
}
