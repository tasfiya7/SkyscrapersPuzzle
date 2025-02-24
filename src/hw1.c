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


int printboard(int size)
{
    printf("    ");
    for (int i = 0; i < size; i++) {
        printf("%d ", top_key[i]);
    }
    printf("\n");
    printf("    ");
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
    printf("\n");
    printf("    ");
    for (int i = 0; i < size; i++) {
        printf("%d ", bottom_key[i]);
    }
    printf("\n");
    return 0;
}


char choosepiece(int size)
{
    printf("Choose a piece (1-%d) or q to quit: ", size );
    char choice;
    scanf(" %c", &choice);
    return choice;
}
int chooserow(int size)
{
    printf("Choose a row (0-%d): ", size-1);
    int rowchoice;
    scanf(" %d", &rowchoice);
    return rowchoice;
}
int choosecolumn(int size)
{
    printf("Choose a column (0-%d): ", size-1);
    int columnchoice;
    scanf(" %d", &columnchoice);
    return columnchoice;
}


bool hasDuplicateInRow(int size, int row, char piece) {
    for (int col = 0; col < size; col++) {
        if (board[row][col] == piece) {
            return true;
        }
    }
    return false;
}


bool hasDuplicateInColumn(int size, int col, char piece) {
    for (int row = 0; row < size; row++) {
        if (board[row][col] == piece) {
            return true;
        }
    }
    return false;
}


bool violatesKey(int size, int row, int col, int val) {
    int value = val - '0';
   
    if(row == 0){
        if (top_key[col] == 1) {
            if (value != size) {
                return true;
            }
        }  
    }
    if (col == 0) {
        if (left_key[row] == 1) {
            if (value != size) {
                return true;
            }
        }  
    }
    if(row == size - 1){
        if (bottom_key[col] == 1) {
            if (value != size) {
                return true;
            }
        }  
    }
    if(col == size - 1){
        if (right_key[row] == 1) {
            if (value != size) {
                return true;
            }
        }  
    }


   
    return false;  
}


void setAscendingOrder(int size) {
    for (int i = 0; i < size; i++) {
        if (top_key[i] == size) {
            for (int j = 0; j < size; j++) {
                board[j][i] = '1' + j;  // Set column in ascending order
            }
        }
        if (bottom_key[i] == size) {
            for (int j = 0; j < size; j++) {
                board[size - 1 - j][i] = '1' + j;  // Set column in ascending order
            }
        }
        if (left_key[i] == size) {
            for (int j = 0; j < size; j++) {
                board[i][j] = '1' + j;  // Set row in ascending order
            }
        }
        if (right_key[i] == size) {
            for (int j = 0; j < size; j++) {
                board[i][size - 1 - j] = '1' + j;  // Set row in ascending order
            }
        }
    }
}




bool checkInitial(int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != '-') {  // Skip empty cells
                for (int k = j + 1; k < size; k++) {
                    if (board[i][j] == board[i][k]) {
                        return true;  // Duplicate found in the row
                    }
                }
            }
        }
    }


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


int checkWinner(int size)
{
    for (int a = 0; a < size; a++) {
         for (int b = 0; b < size; b++) {
            if (board[a][b] == '-'){
                return 0;
            }
        }
    }
    return 1;
}


bool isValidMove(int size, int row, int col, char piece) {
    if (board[row][col] != '-') {
        return false;  
    }
    if (hasDuplicateInRow(size, row, piece) || hasDuplicateInColumn(size, col, piece)) {
        return false;
    }
    if (violatesKey(size, row, col, piece)) {
        return false;  
    }
    return true;
}




int initialize_board(const char *initial_state, const char *keys, int size) {
    (void) initial_state;
    (void) keys;
    (void) size;


    /*size = 4;
    initial_state ="-314-4-23241-1--" ;
    keys = "0003010002003000";
    size = 4;
    initial_state = "3--1---2---31--4";
    keys = "0033300020200421";*/


    for (int i = 0; i < size; i++) {
        top_key[i] = keys[i] - '0';
    }


    for (int i = 0; i < size; i++) {
        bottom_key[i] = keys[size + i] - '0';
    }


    for (int i = 0; i < size; i++) {
        left_key[i] = keys[size + size + i] - '0';
    }


    for (int i = 0; i < size; i++) {
        right_key[i] = keys[size + size + size + i] - '0';
    }


    int idx = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] =  initial_state[idx];
            idx++;
        }
    }


    if(checkInitial(size))
    {
        printf("Invalid initial board state.\n");
        return 0;
    }


    int keepPlaying = 0;
    while(!keepPlaying){


        printboard(size);
        char choice;
        int rowchoice;
        int columnchoice;


        int validChoice = 0;
        while(!validChoice){
            choice = choosepiece(size);
            if (choice == 'q'){
                return 0;
            }
            if (choice >= '1' && choice <= '0' + size) {
                validChoice = 1;
            }else{printf("Invalid choice. ");}
        }
        int validRowChoice = 0;
        while(!validRowChoice){
            rowchoice = chooserow(size);
            if ((rowchoice < 0) || (rowchoice > size))
            {
                printf("Invalid choice. ");
            }else
            {
                validRowChoice = 1;
            }
        }
       
        int validColumnChoice = 0;
        while(!validColumnChoice){
            columnchoice = choosecolumn(size);
            if ((columnchoice < 0) || (columnchoice > size))
            {
                printf("Invalid choice. ");
            }else{
                validColumnChoice = 1;
            }
        }


        if (board[rowchoice][columnchoice] != '-')
        {
        printf("Invalid choice. That space is already occupied.\n");
        }
        else if (hasDuplicateInColumn(size, columnchoice, choice) == 1 || hasDuplicateInRow(size, rowchoice, choice) == 1)
        {
            printf("Invalid choice. There is already a building with that height in that row or column.\n");
        }
        /*else if(violatesKey(size, rowchoice, columnchoice, choice))
        {
            printf("Invalid choice. You violate one of the key requirements.\n");
            //printf(" Whats going on %d this is the number",left_key[rowchoice]);
           // printf("  %d this is the number %d col:%d",left_key[rowchoice], size, columnchoice);
        }*/
        else
        {
            board[rowchoice][columnchoice] = choice;
        }
       
        if(checkWinner(size)){
            if (violatesKey(size, rowchoice, columnchoice, choice))
            {
                printf("Invalid choice. You violate one of the key requirements.\n");
                board[rowchoice][columnchoice] = '-';
            }
            else
            {
                printf("Congratulations, you have filled the board!\n");
                keepPlaying = 1;
            }
        }
    }
    printboard(size);






    return 1;
}


bool solvePuzzle(int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == '-') {
                for (char piece = '1'; piece <= '0' + size; piece++) {
                    if (isValidMove(size, row, col, piece)) {
                        board[row][col] = piece;  


                        if (checkWinner(size)) {
                            printboard(size);
                            return true;  
                        }
                        if (solvePuzzle(size)) {
                            return true;
                        }


                        board[row][col] = '-';
                    }
                }
                return false;  
            }
        }
    }
    return false;  
}
int solve(const char *initial_state, const char *keys, int size){
    (void) initial_state;
    (void) keys;
    (void) size;


   initial_state ="----------------" ;
    keys = "2321321241221332";
    size = 4;


   
    for (int i = 0; i < size; i++) {
        top_key[i] = keys[i] - '0';
    }


    for (int i = 0; i < size; i++) {
        bottom_key[i] = keys[size + i] - '0';
    }


    for (int i = 0; i < size; i++) {
        left_key[i] = keys[size + size + i] - '0';
    }


    for (int i = 0; i < size; i++) {
        right_key[i] = keys[size + size + size + i] - '0';
    }


    int idx = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] =  initial_state[idx];
            idx++;
        }
    }


    printboard(size);
    setAscendingOrder(size);
    printboard(size);


    if (solvePuzzle(size)) {
        printf("Congratulations, the puzzle is solved!\n");
    } else {
        printf("No solution found.\n");
    }
    return 1;
   
}


