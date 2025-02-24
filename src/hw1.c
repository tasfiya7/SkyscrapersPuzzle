#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


#include "hw1.h"

int possibilities[MAX_LENGTH][MAX_LENGTH];

// n lower bits.
#define ALL_VALUES(n) ((1 << (n)) - 1)


int top_key[MAX_LENGTH] = {0};
int bottom_key[MAX_LENGTH] = {0};
int left_key[MAX_LENGTH] = {0};
int right_key[MAX_LENGTH] = {0};


char board[MAX_LENGTH][MAX_LENGTH] = {0};


int length = 5;

// duplicates in the initial board.
bool checkInitial(int size) {
    //rows
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != '-') {  
                for (int k = j + 1; k < size; k++) {
                    if (board[i][j] == board[i][k]) {
                        return true;  
                    }
                }
            }
        }
    }
    //columns
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            if (board[i][j] != '-') {
                for (int k = i + 1; k < size; k++) {
                    if (board[i][j] == board[k][j]) {
                        return true;  
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

	//initital state string
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
                    return 0; 
                }
                row_seen[r_num] = true;
            }
            
            if (col_val != '-') {
                int c_num = col_val - '0';
                if (c_num < 1 || c_num > size || col_seen[c_num]) {
                    return 0; 
                }
                col_seen[c_num] = true;
            }
        }
    }
    
    // if any row is completely filled
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
            if (left_key[i] > 0 && count_visible_buildings(row_temp, size) != left_key[i])
                return 0;
            char row_rev[MAX_LENGTH];
            for (int j = 0; j < size; j++) {
                row_rev[j] = row_temp[size - 1 - j];
            }
            if (right_key[i] > 0 && count_visible_buildings(row_rev, size) != right_key[i])
                return 0;
        }
    }
    //columns
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
    
    //top and bottom keys
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
    
    //left and right keys
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
        if (left_key[row] > 0 && count_visible_buildings(row_temp, size) != left_key[row])
            return true;
        char row_rev[MAX_LENGTH];
        for (int j = 0; j < size; j++) {
            row_rev[j] = row_temp[size - 1 - j];
        }
        if (right_key[row] > 0 && count_visible_buildings(row_rev, size) != right_key[row])
            return true;
    }
    
    // complete the column
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
    if (board[row][col] != '-') {
        printf("Invalid choice. That space is already occupied. \n");
        return false;
    }
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
        
    // complete a row or column.
    if (violates_key_requirements(size, piece, row, col)) {
        printf("Invalid choice. You violate one of the key requirements.\n");
        return false;
    }
        
    return true;
}
    


void handle_user_input(int size) {
    #ifdef TESTING
    // When testing automatically
    return;
#endif
    char choice;
    int row;
    int col;
    bool exit_flag = false;
    while (1) {
        printf("Choose a piece (1-%d) or q to quit: ", size);
        int result = scanf(" %c", &choice);
        if (result == EOF) {  // No more input
            break;
        }
        if (result != 1) {
            while (getchar() != '\n'); 
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
                    while (getchar() != '\n') { }
                    printf("Invalid choice. ");

                        continue;  
                    }
                    break;  
                }
        if (exit_flag)
            break;
        
        // Prompt for column 
        while (1) {
            printf("Choose a column (0-%d): ", size - 1);
            result = scanf("%d", &col);
            if (result == EOF) {
                exit_flag = true;
                break;
        }
        if (result != 1 || col < 0 || col >= size) {
            while (getchar() != '\n') { }
            printf("Invalid choice. ");

                continue;  
        }
            break;  
        }
        if (exit_flag)
            break;
        
    
        if (!is_valid_move(size, choice, row, col)) {
            print_board(size);  // Reprint board after an invalid move
            continue;
        }
    
        board[row][col] = choice;
    

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

    
    
int mask_to_value(int mask) {
    int val = 1;
    while (mask >>= 1)
        val++;
    return val;
}

//mask has one bit set.
bool is_single(int mask) {
    return mask && !(mask & (mask - 1));
}

// Initialize possibilities 
void init_possibilities(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == '-') {
                possibilities[i][j] = ALL_VALUES(size);
            } else {
                int val = board[i][j] - '0';
                possibilities[i][j] = 1 << (val - 1);
            }
        }
    }
}

// HEURISTIC #1:
void apply_edge_clue_initialization(int size) {
    //top
    for (int j = 0; j < size; j++) {
        int key = top_key[j];
        if (key == 1) {
            possibilities[0][j] = 1 << (size - 1);
            board[0][j] = '0' + size;
        } else if (key == size) {
            for (int i = 0; i < size; i++) {
                possibilities[i][j] = 1 << i; 
                board[i][j] = '1' + i;
            }
        } else if (key > 1 && key < size) {
            for (int d = 0; d < size; d++) {
                int start = size - key + 2 + d;
                for (int val = start; val <= size; val++) {
                    possibilities[d][j] &= ~(1 << (val - 1));
                }
            }
        }
    }
    // bottom 
    for (int j = 0; j < size; j++) {
        int key = bottom_key[j];
        if (key == 1) {
            possibilities[size - 1][j] = 1 << (size - 1);
            board[size - 1][j] = '0' + size;
        } else if (key == size) {
            for (int i = 0; i < size; i++) {
                possibilities[size - 1 - i][j] = 1 << i;
                board[size - 1 - i][j] = '1' + i;
            }
        } else if (key > 1 && key < size) {
            for (int d = 0; d < size; d++) {
                int start = size - key + 2 + d;
                for (int val = start; val <= size; val++) {
                    possibilities[size - 1 - d][j] &= ~(1 << (val - 1));
                }
            }
        }
    }
    // left 
    for (int i = 0; i < size; i++) {
        int key = left_key[i];
        if (key == 1) {
            possibilities[i][0] = 1 << (size - 1);
            board[i][0] = '0' + size;
        } else if (key == size) {
            for (int j = 0; j < size; j++) {
                possibilities[i][j] = 1 << j;
                board[i][j] = '1' + j;
            }
        } else if (key > 1 && key < size) {
            for (int d = 0; d < size; d++) {
                int start = size - key + 2 + d;
                for (int val = start; val <= size; val++) {
                    possibilities[i][d] &= ~(1 << (val - 1));
                }
            }
        }
    }
    // Right
    for (int i = 0; i < size; i++) {
        int key = right_key[i];
        if (key == 1) {
            possibilities[i][size - 1] = 1 << (size - 1);
            board[i][size - 1] = '0' + size;
        } else if (key == size) {
            for (int j = 0; j < size; j++) {
                possibilities[i][size - 1 - j] = 1 << j;
                board[i][size - 1 - j] = '1' + j;
            }
        } else if (key > 1 && key < size) {
            for (int d = 0; d < size; d++) {
                int start = size - key + 2 + d;
                for (int val = start; val <= size; val++) {
                    possibilities[i][size - 1 - d] &= ~(1 << (val - 1));
                }
            }
        }
    }
}

// HEURISTIC #2:
bool apply_constraint_propagation(int size) {
    bool progress = false;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (is_single(possibilities[i][j])) {
                int fixed = possibilities[i][j];
                for (int col = 0; col < size; col++) {
                    if (col != j) {
                        int old = possibilities[i][col];
                        possibilities[i][col] &= ~fixed;
                        if (possibilities[i][col] != old)
                            progress = true;
                    }
                }
                for (int row = 0; row < size; row++) {
                    if (row != i) {
                        int old = possibilities[row][j];
                        possibilities[row][j] &= ~fixed;
                        if (possibilities[row][j] != old)
                            progress = true;
                    }
                }
            }
        }
    }
    return progress;
}

//HEURISTIC #3
bool apply_process_of_elimination(int size) {
    bool progress = false;
    // rows
    for (int i = 0; i < size; i++) {
        for (int val = 1; val <= size; val++) {
            int bit = 1 << (val - 1);
            int count = 0, pos = -1;
            for (int j = 0; j < size; j++) {
                if (possibilities[i][j] & bit) {
                    count++;
                    pos = j;
                }
            }
            if (count == 1 && !is_single(possibilities[i][pos])) {
                possibilities[i][pos] = bit;
                board[i][pos] = '0' + val;
                progress = true;
            }
        }
    }
    // columns
    for (int j = 0; j < size; j++) {
        for (int val = 1; val <= size; val++) {
            int bit = 1 << (val - 1);
            int count = 0, pos = -1;
            for (int i = 0; i < size; i++) {
                if (possibilities[i][j] & bit) {
                    count++;
                    pos = i;
                }
            }
            if (count == 1 && !is_single(possibilities[pos][j])) {
                possibilities[pos][j] = bit;
                board[pos][j] = '0' + val;
                progress = true;
            }
        }
    }
    return progress;
}

// HEURISTIC #4
int visible_count_in_sequence(int seq[], int len) {
    int count = 0, max = 0;
    for (int i = 0; i < len; i++) {
        if (seq[i] > max) {
            max = seq[i];
            count++;
        }
    }
    return count;
}

// valid sequences for row
void generate_valid_row_sequences(int size, int row, int col, int current_seq[],
                                  bool used[], int union_vals[], int *valid_count) {
    if (col == size) {
        if (left_key[row] > 0 && visible_count_in_sequence(current_seq, size) != left_key[row])
            return;
        int rev_seq[MAX_LENGTH];
        for (int j = 0; j < size; j++)
            rev_seq[j] = current_seq[size - 1 - j];
        if (right_key[row] > 0 && visible_count_in_sequence(rev_seq, size) != right_key[row])
            return;
       
        for (int j = 0; j < size; j++) {
            union_vals[j] |= (1 << (current_seq[j] - 1));
        }
        (*valid_count)++;
        return;
    }
    if (is_single(possibilities[row][col])) {
        int fixed = mask_to_value(possibilities[row][col]);
        if (used[fixed]) return;
        used[fixed] = true;
        current_seq[col] = fixed;
        generate_valid_row_sequences(size, row, col + 1, current_seq, used, union_vals, valid_count);
        used[fixed] = false;
        return;
    }
    for (int val = 1; val <= size; val++) {
        int bit = 1 << (val - 1);
        if ((possibilities[row][col] & bit) && !used[val]) {
            used[val] = true;
            current_seq[col] = val;
            generate_valid_row_sequences(size, row, col + 1, current_seq, used, union_vals, valid_count);
            used[val] = false;
        }
    }
}

void filter_row_possibilities(int size, int row) {
    int union_vals[MAX_LENGTH] = {0};
    int current_seq[MAX_LENGTH] = {0};
    bool used[9] = {false}; 
    int valid_count = 0;
    generate_valid_row_sequences(size, row, 0, current_seq, used, union_vals, &valid_count);
    if (valid_count > 0) {
        for (int j = 0; j < size; j++) {
            if (!is_single(possibilities[row][j])) {
                possibilities[row][j] &= union_vals[j];
                if (is_single(possibilities[row][j]))
                    board[row][j] = '0' + mask_to_value(possibilities[row][j]);
            }
        }
    }
}

void generate_valid_col_sequences(int size, int col, int row, int current_seq[],
                                  bool used[], int union_vals[], int *valid_count) {
    if (row == size) {
        if (top_key[col] > 0 && visible_count_in_sequence(current_seq, size) != top_key[col])
            return;
        int rev_seq[MAX_LENGTH];
        for (int i = 0; i < size; i++)
            rev_seq[i] = current_seq[size - 1 - i];
        if (bottom_key[col] > 0 && visible_count_in_sequence(rev_seq, size) != bottom_key[col])
            return;
        for (int i = 0; i < size; i++) {
            union_vals[i] |= (1 << (current_seq[i] - 1));
        }
        (*valid_count)++;
        return;
    }
    if (is_single(possibilities[row][col])) {
        int fixed = mask_to_value(possibilities[row][col]);
        if (used[fixed]) return;
        used[fixed] = true;
        current_seq[row] = fixed;
        generate_valid_col_sequences(size, col, row + 1, current_seq, used, union_vals, valid_count);
        used[fixed] = false;
        return;
    }
    for (int val = 1; val <= size; val++) {
        int bit = 1 << (val - 1);
        if ((possibilities[row][col] & bit) && !used[val]) {
            used[val] = true;
            current_seq[row] = val;
            generate_valid_col_sequences(size, col, row + 1, current_seq, used, union_vals, valid_count);
            used[val] = false;
        }
    }
}

void filter_col_possibilities(int size, int col) {
    int union_vals[MAX_LENGTH] = {0};
    int current_seq[MAX_LENGTH] = {0};
    bool used[9] = {false};
    int valid_count = 0;
    generate_valid_col_sequences(size, col, 0, current_seq, used, union_vals, &valid_count);
    if (valid_count > 0) {
        for (int i = 0; i < size; i++) {
            if (!is_single(possibilities[i][col])) {
                possibilities[i][col] &= union_vals[i];
                if (is_single(possibilities[i][col]))
                    board[i][col] = '0' + mask_to_value(possibilities[i][col]);
            }
        }
    }
}

bool apply_clue_elimination(int size) {
    bool progress = false;
    // rows
    for (int i = 0; i < size; i++) {
        int before = 0, after = 0;
        for (int j = 0; j < size; j++) {
            before += possibilities[i][j];
        }
        filter_row_possibilities(size, i);
        for (int j = 0; j < size; j++) {
            after += possibilities[i][j];
        }
        if (after != before) progress = true;
    }
    //columns
    for (int j = 0; j < size; j++) {
        int before = 0, after = 0;
        for (int i = 0; i < size; i++) {
            before += possibilities[i][j];
        }
        filter_col_possibilities(size, j);
        for (int i = 0; i < size; i++) {
            after += possibilities[i][j];
        }
        if (after != before) progress = true;
    }
    return progress;
}


// If the heuristics doent solve 
bool backtracking_solve(int size) {
    int i, j;
    bool found = false;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == '-') {
                found = true;
                break;
            }
        }
        if (found) break;
    }
    if (!found) {
        return validate_visibility(size);
    }
    for (int val = 1; val <= size; val++) {
        char c = '0' + val;
        bool valid = true;
        for (int k = 0; k < size; k++) {
            if (board[i][k] == c || board[k][j] == c) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        board[i][j] = c;
        if (backtracking_solve(size)) return true;
        board[i][j] = '-';
    }
    return false;
}

void solve(const char *initial_state, const char *keys, int size) {
    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = initial_state[index++];
        }
    }
    index = 0;
    for (int i = 0; i < size; i++) {
        top_key[i] = keys[index++] - '0';
    }
    for (int i = 0; i < size; i++) {
        bottom_key[i] = keys[index++] - '0';
    }
    for (int i = 0; i < size; i++) {
        left_key[i] = keys[index++] - '0';
    }
    for (int i = 0; i < size; i++) {
        right_key[i] = keys[index++] - '0';
    }
    
    init_possibilities(size);
    apply_edge_clue_initialization(size);
    
    bool progress = true;
    while (progress) {
        progress = false;
        if (apply_constraint_propagation(size))
            progress = true;
        if (apply_process_of_elimination(size))
            progress = true;
        if (apply_clue_elimination(size))
            progress = true;
    }
  
    bool complete = true;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == '-') {
                complete = false;
                break;
            }
        }
        if (!complete) break;
    }
    if (!complete) {
        backtracking_solve(size);
    }

    print_board(size);
}