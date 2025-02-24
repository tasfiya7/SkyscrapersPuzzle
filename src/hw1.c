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


int initialize_board(const char *initial_state, const char *keys, int size) {

	if (size < 2 || size > MAX_LENGTH) {
        return 0;
    }


	//parse initital state string
	int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = initial_state[index];
            index++;
        }
    }



	//key string 
	index = 0;
    for (int i = 0; i < size; i++) top_key[i] = keys[index++] - '0';
    for (int i = 0; i < size; i++) bottom_key[i] = keys[index++] - '0';
    for (int i = 0; i < size; i++) left_key[i] = keys[index++] - '0';
    for (int i = 0; i < size; i++) right_key[i] = keys[index++] - '0';




	//validate board state
	for (int i = 0; i < size; i++) {
        bool row_seen[MAX_LENGTH + 1] = {false};
        bool col_seen[MAX_LENGTH + 1] = {false};
        
        for (int j = 0; j < size; j++) {
            char row_val = board[i][j];
            char col_val = board[j][i];
            
            if (row_val != '-') {
                int r_num = row_val - '0';
                if (r_num < 1 || r_num > size || row_seen[r_num]) {
                    return 0; // Invalid number or duplicate in row
                }
                row_seen[r_num] = true;
            }
            
            if (col_val != '-') {
                int c_num = col_val - '0';
                if (c_num < 1 || c_num > size || col_seen[c_num]) {
                    return 0; // Invalid number or duplicate in column
                }
                col_seen[c_num] = true;
            }
        }
    }
    
    return 1;
}




void print_board(int size) {
    printf("    ");
    for (int i = 0; i < size; i++) {
        printf("%d ", top_key[i]);
    }
    printf("\n    ");
    for (int i = 0; i < size; i++) {
        printf("v ");
    }
    printf("\n");
    
    for (int i = 0; i < size; i++) {
        printf("%d > ", left_key[i]);
        for (int j = 0; j < size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("< %d\n", right_key[i]);
    }
    
    printf("    ");
    for (int i = 0; i < size; i++) {
        printf("^ ");
    }
    printf("\n    ");
    for (int i = 0; i < size; i++) {
        printf("%d ", bottom_key[i]);
    }
    printf("\n");
}


int count_visible_buildings(char line[MAX_LENGTH], int size) {
    int max_height = 0;
    int visible_count = 0;
    for (int i = 0; i < size; i++) {
        if (line[i] > max_height) {
            max_height = line[i];
            visible_count++;
        }
    }
    return visible_count;
}

bool validate_visibility(int size) {
    char temp[MAX_LENGTH];
    
    // Check top and bottom keys
    for (int col = 0; col < size; col++) {
        for (int row = 0; row < size; row++) {
            temp[row] = board[row][col];
        }
        if (top_key[col] > 0 && count_visible_buildings(temp, size) != top_key[col]) {
            return false;
        }
        
        for (int row = 0; row < size; row++) {
            temp[row] = board[size - 1 - row][col];
        }
        if (bottom_key[col] > 0 && count_visible_buildings(temp, size) != bottom_key[col]) {
            return false;
        }
    }
    
    // Check left and right keys
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            temp[col] = board[row][col];
        }
        if (left_key[row] > 0 && count_visible_buildings(temp, size) != left_key[row]) {
            return false;
        }
        
        for (int col = 0; col < size; col++) {
            temp[col] = board[row][size - 1 - col];
        }
        if (right_key[row] > 0 && count_visible_buildings(temp, size) != right_key[row]) {
            return false;
        }
    }
    
    return true;
}



    bool is_valid_move(int size, char piece, int row, int col) {
        // Check if the cell is already occupied
        if (board[row][col] != '-') {
            printf("Invalid choice. That space is already occupied. \n");
            return false;
        }
        
        // Check for duplicate piece in the row or column
        bool duplicate = false;
        // Check row for duplicate
        for (int j = 0; j < size; j++) {
            if (board[row][j] == piece) {
                duplicate = true;
                break;
            }
        }
        // If not found in row, check column for duplicate
        if (!duplicate) {
            for (int i = 0; i < size; i++) {
                if (board[i][col] == piece) {
                    duplicate = true;
                    break;
                }
            }
        }
        if (duplicate) {
            printf("Invalid choice. There is already a building with that height in that row or column. \n");
            return false;
        }
        
        return true;
    }
    


    void handle_user_input(int size) {
        char choice;
        int row, col;
        bool exit_flag = false;
        while (1) {
            printf("Choose a piece (1-%d) or q to quit: ", size);
            int result = scanf(" %c", &choice);
            if (result == EOF) {  // No more input, exit gracefully
                break;
            }
            if (result != 1) {
                while (getchar() != '\n'); // clear input buffer
                printf("Invalid choice.\n");
                continue;
            }
            if (choice == 'q') {
                printf("Game exited.\n");
                break;
            }
            if (choice < '1' || choice > ('0' + size)) {
                printf("Invalid choice. ");
                continue;
            }
    
            // Prompt for row
                while (1) {
                    printf("Choose a row (0-%d): ", size - 1);
                    result = scanf("%d", &row);
                    if (result == EOF) {
                        exit_flag = true;
                        break;
                    }
                    if (result != 1 || row < 0 || row >= size) {
                        while (getchar() != '\n'); // clear input buffer
                        printf("Invalid choice. ");
                        continue;  // re-prompt for row
                    }
                    break;  // valid row entered
                }
                if (exit_flag)
                    break;
        
                // Prompt for column using its own loop.
                while (1) {
                    printf("Choose a column (0-%d): ", size - 1);
                    result = scanf("%d", &col);
                    if (result == EOF) {
                        exit_flag = true;
                        break;
                    }
                    if (result != 1 || col < 0 || col >= size) {
                        while (getchar() != '\n'); // clear input buffer
                        printf("Invalid choice. ");
                        continue;  // re-prompt for column
                    }
                    break;  // valid column entered
                }
                if (exit_flag)
                    break;
        
    
            if (!is_valid_move(size, choice, row, col)) {
                print_board(size);  // Reprint board after an invalid move
                continue;
            }
    
            board[row][col] = choice;
    
            // Check if board is full.
            bool board_full = true;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board[i][j] == '-') {
                        board_full = false;
                        break;
                    }
                }
                if (!board_full)
                    break;
            }
    
            if (board_full && validate_visibility(size)) {
                printf("Congratulations, you have filled the board!\n");
                print_board(size);
                break;
            }
    
            print_board(size);
        }
}

    
    

int solve(const char *initial_state, const char *keys, int size){
	(void) initial_state;
	(void) keys;
	(void) size;
	
	return 1;
	
}