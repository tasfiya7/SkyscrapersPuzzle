#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>  


#include "hw1.h"

int top_key[MAX_LENGTH] = {0};
int bottom_key[MAX_LENGTH] = {0};
int left_key[MAX_LENGTH] = {0};
int right_key[MAX_LENGTH] = {0};

char board[MAX_LENGTH][MAX_LENGTH] = {0};

int length = 5;


// Function to set ascending order based on keys
void setAscendingOrder(int size) {
    for (int i = 0; i < size; i++) {
        if (top_key[i] == size) {
            for (int j = 0; j < size; j++) board[j][i] = '1' + j;
        }
        if (bottom_key[i] == size) {
            for (int j = 0; j < size; j++) board[size - 1 - j][i] = '1' + j;
        }
        if (left_key[i] == size) {
            for (int j = 0; j < size; j++) board[i][j] = '1' + j;
        }
        if (right_key[i] == size) {
            for (int j = 0; j < size; j++) board[i][size - 1 - j] = '1' + j;
        }
    }
}

// Function to check for duplicates in the initial board state
bool checkInitial(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != '-') {
                for (int k = j + 1; k < size; k++) {
                    if (board[i][j] == board[i][k]) return true; // Duplicate in row
                }
                for (int k = i + 1; k < size; k++) {
                    if (board[i][j] == board[k][j]) return true; // Duplicate in column
                }
            }
        }
    }
    return false;
}

// Function to initialize the board
int initialize_board(const char *initial_state, const char *keys, int size) {
    if (size < 2 || size > MAX_LENGTH) return 0;

    // Parse initial state string
    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = initial_state[index++];
        }
    }

    // Parse key string
    index = 0;
    for (int i = 0; i < size; i++) top_key[i] = keys[index++] - '0';
    for (int i = 0; i < size; i++) bottom_key[i] = keys[index++] - '0';
    for (int i = 0; i < size; i++) left_key[i] = keys[index++] - '0';
    for (int i = 0; i < size; i++) right_key[i] = keys[index++] - '0';

    // Set ascending order based on keys
    setAscendingOrder(size);

    // Validate initial board state
    if (checkInitial(size)) {
        printf("Invalid initial board state.\n");
        return 0;
    }

    return 1;
}

// Function to print the board
void print_board(int size) {
    printf("    ");
    for (int i = 0; i < size; i++) printf("%d ", top_key[i]);
    printf("\n    ");
    for (int i = 0; i < size; i++) printf("v ");
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%d > ", left_key[i]);
        for (int j = 0; j < size; j++) printf("%c ", board[i][j]);
        printf("< %d\n", right_key[i]);
    }

    printf("    ");
    for (int i = 0; i < size; i++) printf("^ ");
    printf("\n    ");
    for (int i = 0; i < size; i++) printf("%d ", bottom_key[i]);
    printf("\n");
}

// Function to check if a move is valid
bool is_valid_move(int size, char piece, int row, int col) {
    if (board[row][col] != '-') {
        printf("Invalid choice. That space is already occupied.\n");
        return false;
    }

    // Check for duplicates in row and column
    for (int j = 0; j < size; j++) {
        if (board[row][j] == piece || board[j][col] == piece) {
            printf("Invalid choice. There is already a building with that height in that row or column.\n");
            return false;
        }
    }

    // Check key constraints
    int value = piece - '0';
    if ((row == 0 && top_key[col] == 1 && value != size) ||
        (col == 0 && left_key[row] == 1 && value != size) ||
        (row == size - 1 && bottom_key[col] == 1 && value != size) ||
        (col == size - 1 && right_key[row] == 1 && value != size)) {
        printf("Invalid choice. You violate one of the key requirements.\n");
        return false;
    }

    return true;
}

// Function to handle user input
void handle_user_input(int size) {
    char choice;
    int row, col;

    while (1) {
        choice = choosepiece(size);
        if (choice == 'q') {
            printf("Game exited.\n");
            return;
        }

        row = chooserow(size);
        col = choosecolumn(size);

        if (!is_valid_move(size, choice, row, col)) {
            print_board(size);
            continue;
        }

        board[row][col] = choice;
        print_board(size);

        if (checkWinner(size)) {
            printf("Congratulations, you have filled the board!\n");
            return;
        }
    }
}

// Function to check if the board is fully filled
bool checkWinner(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == '-') return false;
        }
    }
    return true;
}

// Function to solve the puzzle (placeholder)
int solve(const char *initial_state, const char *keys, int size) {
    (void) initial_state;
    (void) keys;
    (void) size;
    return 1;
}

