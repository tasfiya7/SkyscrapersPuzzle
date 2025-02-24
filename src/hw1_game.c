#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s size initial_state keys\n", argv[0]);
        return 0;
    }
    int size = (int)strtoul(argv[1], NULL, 10);
    if (!initialize_board(argv[2], argv[3], size)) {
        printf("Invalid initial board state.\n");
        return 0;  // exit gracefully with 0
    }
    print_board(size);
    handle_user_input(size);
    return 0;
}