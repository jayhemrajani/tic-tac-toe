#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>



/* I'm going to make a tic-tac-toe game as my first "project"
 * in terms of coding standard, this follows what I learned 
 * as a student at Purdue University this last year. Also a
 * bit of a warning, this computer has no logic in its moves
 * and you will most likely be able to beat it even if you make
 * a couple mistakes here and there. Good luck!
 */

void reset_board();
void print_board();
int check_spaces();
void player_move();
void computer_move();
char check_winner();
void print_winner(char);

char board[3][3];
const char player = 'x';
const char computer = 'o';

int main() {

    char choice;
    char winner = ' ';
    


    do {

        winner = ' ';
        choice = ' ';
        reset_board();

        while (winner == ' ' && check_spaces()) {
            print_board();
            player_move();
            winner = check_winner();

            if((winner != ' ') || (check_spaces() == 0)) {
                break;
            }

            computer_move();
            winner = check_winner();

            if((winner != ' ') || (check_spaces() == 0)) {
                break;
            }
        }
        print_board();
        print_winner(winner);

        printf("Do you want to play again? (Y/N)\n");
        scanf(" %c", &choice);

        choice = toupper(choice);
    } while (choice == 'Y');

    if (choice == 'N') {
        printf("Thanks for playing my game.\n");
    }
    return 0;
}

void reset_board() {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void print_board() {

    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int check_spaces() {
    
    int free =9;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ')  {
                free--;
            }
        }
    }
    return free; //if 0 is returned, game over
}

void player_move() {

    int x; //row number
    int y; //column number

    do {
        printf("Which row would you like to use?\n");
        scanf("%d", &x);
        x = x - 1;
        printf("Which column would you like to use?\n");
        scanf("%d", &y);
        y = y - 1;

        if(board[x][y] != ' ') {
            printf("You can't move there, try again\n");
        }
        else {
            board[x][y] = player;
            break;
        }
    } while(board[x][y] != ' ');
}

void computer_move() {

    //seed for random generation srand(), thanks Turkstra

    srand(time(0));

    int x;
    int y;

    if (check_spaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while(board[x][y] != ' ');

        board[x][y] = computer;
    }
    else {
        print_winner(' ');
    }
}

char check_winner() {

    //checking the rows for a winner
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1]) && (board[i][0]) == board[i][2]) {
            return board[i][1];
        }
    }

    //checking the columns for a winner
    for (int j = 0; j < 3; j++) {
        if ((board[0][j] == board[1][j]) && (board[0][j]) == board[2][j]) {
            return board[1][j];
        }
    }

    //checking for diagonals
    if ((board[0][0] == board[1][1]) && (board[0][0]) == board[2][2]) {
            return board[1][1];
    }
    if ((board[0][2] == board[1][1]) && (board[0][2]) == board[2][0]) {
            return board[1][1];
    }

    return ' ';

}

void print_winner(char winner) {

    if (winner == player) {
        printf("You have won the game\n");
    }
    else if (winner == computer) {
        printf("Sorry! You lost... better luck next time!\n");
    }
    else {
        printf("You outsmarted each other, I suppose\n");
    }
}
