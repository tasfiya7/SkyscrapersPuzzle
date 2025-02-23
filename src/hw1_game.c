#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"

int main(int argc, char **argv) {
    assert(argc == 4); //we want a size, board state, and a list of keys

    int size = (int)strtoul(argv[1], NULL, 10);
	if (!initialize_board(argv[2], argv[3], size)) {
        printf("Invalid initial board state.\n");
        return 1; // Exit with an error code
    }
    
 
    print_board(size);
    handle_user_input(size);
    return 0;
}