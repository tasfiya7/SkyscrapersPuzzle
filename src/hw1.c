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


int initialize_board(const char *initial_state, const char *keys, int size) {
	(void) initial_state;
	(void) keys;
	(void) size;

	if (size < 4 || size > MAX_LENGTH) {
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


int solve(const char *initial_state, const char *keys, int size){
	(void) initial_state;
	(void) keys;
	(void) size;
	
	return 1;
	
}