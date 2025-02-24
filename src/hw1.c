#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


#include "hw1.h"


int top_key[MAX_LENGTH] = {0};
int bottom_key[MAX_LENGTH] = {0};
int left_key[MAX_LENGTH] = {0};
int right_key[MAX_LENGTH] = {0};


char board[MAX_LENGTH][MAX_LENGTH] = {0};


int length = 5;

// Helper function to check for duplicates in the initial board.
bool checkInitial(int size) {
    // Check rows for duplicates.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != '-') {  // skip empty cells
                for (int k = j + 1; k < size; k++) {
                    if (board[i][j] == board[i][k]) {
                        return true;  // duplicate found in the row
                    }
                }
            }
        }
    }
    // Check columns for duplicates.
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            if (board[i][j] != '-') {
                for (int k = i + 1; k < size; k++) {
                    if (board[i][j] == board[k][j]) {
                        return true;  // duplicate found in the column
                    }
                }
            }
        }
    }
    return false;
}


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


    // Check for duplicate placements in the initial board.
    if (checkInitial(size)) {
        return 0;
    }



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
    
    // Additional check: if any row is completely filled, its visible count must match the keys.
    for (int i = 0; i < size; i++) {
        bool complete = true;
        char row_temp[MAX_LENGTH];
        for (int j = 0; j < size; j++) {
            row_temp[j] = board[i][j];
            if (board[i][j] == '-') {
                complete = false;
            }
        }
        if (complete) {
            // Check left key.
            if (left_key[i] > 0 && count_visible_buildings(row_temp, size) != left_key[i])
                return 0;
            // Check right key (reverse the row).
            char row_rev[MAX_LENGTH];
            for (int j = 0; j < size; j++) {
                row_rev[j] = row_temp[size - 1 - j];
            }
            if (right_key[i] > 0 && count_visible_buildings(row_rev, size) != right_key[i])
                return 0;
        }
    }

    // Similarly, check complete columns.
    for (int j = 0; j < size; j++) {
        bool complete = true;
        char col_temp[MAX_LENGTH];
        for (int i = 0; i < size; i++) {
            col_temp[i] = board[i][j];
            if (board[i][j] == '-') {
                complete = false;
            }
        }
        if (complete) {
            if (top_key[j] > 0 && count_visible_buildings(col_temp, size) != top_key[j])
                return 0;
            char col_rev[MAX_LENGTH];
            for (int i = 0; i < size; i++) {
                col_rev[i] = col_temp[size - 1 - i];
            }
            if (bottom_key[j] > 0 && count_visible_buildings(col_rev, size) != bottom_key[j])
                return 0;
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


bool violates_key_requirements(int size, char piece, int row, int col) {

    bool row_complete = true;
    char row_temp[MAX_LENGTH];
    for (int j = 0; j < size; j++) {
        if (j == col) {
            row_temp[j] = piece;
        } else {
            row_temp[j] = board[row][j];
            if (board[row][j] == '-') {
                row_complete = false;
            }
        }
    }
    if (row_complete) {
        // Check left key if provided.
        if (left_key[row] > 0 && count_visible_buildings(row_temp, size) != left_key[row])
            return true;
        // Check right key: build a reversed copy.
        char row_rev[MAX_LENGTH];
        for (int j = 0; j < size; j++) {
            row_rev[j] = row_temp[size - 1 - j];
        }
        if (right_key[row] > 0 && count_visible_buildings(row_rev, size) != right_key[row])
            return true;
    }
    
    // Check if placing piece would complete the column.
    bool col_complete = true;
    char col_temp[MAX_LENGTH];
    for (int i = 0; i < size; i++) {
        if (i == row) {
            col_temp[i] = piece;
        } else {
            col_temp[i] = board[i][col];
            if (board[i][col] == '-') {
                col_complete = false;
            }
        }
    }
    if (col_complete) {
        if (top_key[col] > 0 && count_visible_buildings(col_temp, size) != top_key[col])
            return true;
        char col_rev[MAX_LENGTH];
        for (int i = 0; i < size; i++) {
            col_rev[i] = col_temp[size - 1 - i];
        }
        if (bottom_key[col] > 0 && count_visible_buildings(col_rev, size) != bottom_key[col])
            return true;
    }
    
    return false;
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
        for (int i = 0; i < size; i++) {
            if (board[i][col] == piece) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            printf("Invalid choice. There is already a building with that height in that row or column.\n");
            return false;
        }
        
        // Check key requirements if this move would complete a row or column.
        if (violates_key_requirements(size, piece, row, col)) {
            printf("Invalid choice. You violate one of the key requirements.\n");
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