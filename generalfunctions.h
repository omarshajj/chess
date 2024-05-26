#pragma once

#include <iostream>
#include <iomanip>

using namespace std;
const int BOARD_SIZE = 8;
void updateBchecksboard(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE]);
void updateWchecksboard(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE]);

void storepreviousboard(char board[BOARD_SIZE][BOARD_SIZE],char previousboard[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0;i < BOARD_SIZE;i++) {//this is used for en passant storing the board before the opponents prior move was made
        for (int j = 0;j < BOARD_SIZE;j++) {
           previousboard[i][j] = board[i][j];
        }
    }
}
void mapcoordinates(string coordinate,int& row, int& col) {//this function will map the string input of the user to indexes for rows and cols
    string coordinateboard[BOARD_SIZE][BOARD_SIZE];
    char horizontal = 'a';
    char vertical = '1';
    bool same = false;
    for (int i = 0;i < BOARD_SIZE;i++) {// this loop will initialize all the squares on the 2d array to store the corresponding string input
        for (int j = 0;j < BOARD_SIZE;j++) {
            horizontal = 'a' + j;
            vertical = '1' + (7 - i);
            coordinateboard[i][j] = horizontal;
            coordinateboard[i][j] += vertical;
        }
    }
    for (int i = 0;i < BOARD_SIZE;i++) {//compares the input of the user to all squares and returns indexes of corresponding squares 
        for (int j = 0;j < BOARD_SIZE;j++) {
            if (coordinate == coordinateboard[i][j]) {
                row = i;
                col = j;
                same = true;
            }
        }
    }
    if (same == false) {// assigns values outside the board to be flagged as invalid if an invalid input is given
        row = 9;
        col = 9;
    }
}

void Wpawnpromotion(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE]) {// checks for pawn promotion for the white pieces 
    for (int j = 0;j < BOARD_SIZE;j++) {
        if (board[0][j] == 'P') {
            board[0][j] = 'Q';
        }
    }
    updateBchecksboard(board, Bchecksboard);

}
void Bpawnpromotion(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE]) {// checks for pawn promotion for the black pieces 
    for (int j = 0;j < BOARD_SIZE;j++) {
        if (board[7][j] == 'p') {
            board[7][j] = 'q';
        }
    }
    updateWchecksboard(board, Wchecksboard);

}



bool checkforWcheck(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE],bool properrun) {//this function checks for a check on the white king and return true if the king is checked 
    bool ischeck = false;
    for (int i = 0;i < BOARD_SIZE;i++) { 
        for (int j = 0;j < BOARD_SIZE;j++) {
            if (board[i][j] == 'K' && Bchecksboard[i][j] == 'c') {
                if (properrun == true) {
                    cout << "the white king is under check " << endl;
                }
                ischeck = true;
            }
        }
    }

    return ischeck;
}
bool checkforBcheck(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE],bool properrun) {//this function checks for a check on the white king and return true if the king is checked
    bool ischeck = false;
    for (int i = 0;i < BOARD_SIZE;i++) {
        for (int j = 0;j < BOARD_SIZE;j++) {
            if (board[i][j] == 'k' && Wchecksboard[i][j] == 'c') {
                if (properrun == true) {
                    cout << "the black king is under check " << endl;
                }
                ischeck = true;
            }

        }
    }
    return ischeck;
}

void updateBchecksboard(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE]) {//updates the checkboard done by black pieces
    for (int i = 0; i < BOARD_SIZE;i++) {// initializes checkboard to be empty
        for (int j = 0;j < BOARD_SIZE;j++) {
            Bchecksboard[i][j] = ' ';
        }
    }

    for (int i = 0; i < BOARD_SIZE;i++) {
        for (int j = 0;j < BOARD_SIZE;j++) {

            if (board[i][j] == 'p') {// places the checks done by pawns on the board
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {
                    Bchecksboard[i + 1][j - 1] = 'c';
                }
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {
                    Bchecksboard[i + 1][j + 1] = 'c';
                }
            }
            else if (board[i][j] == 'k') {// places the checks done by the king on the board
                if (0 <= i && i < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {
                    Bchecksboard[i][j - 1] = 'c';
                }
                if (0 <= i && i < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {
                    Bchecksboard[i][j + 1] = 'c';
                }
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {
                    Bchecksboard[i - 1][j - 1] = 'c';
                }
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {
                    Bchecksboard[i - 1][j + 1] = 'c';
                }
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {
                    Bchecksboard[i + 1][j - 1] = 'c';
                }
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {
                    Bchecksboard[i + 1][j + 1] = 'c';
                }
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j && j < BOARD_SIZE) {
                    Bchecksboard[i - 1][j] = 'c';
                }
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j && j < BOARD_SIZE) {
                    Bchecksboard[i + 1][j] = 'c';
                }

            }
            else if (board[i][j] == 'q') {// places the checks done by the queen on the board
           
                int f = 1;
                while (0 <= i - f && i - f < BOARD_SIZE && (board[i - f][j] == ' '|| board[i - f][j] == 'K')) {//up checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i - f][j] = 'c';
                    f++;
                }if (0 <= i - f && i - f < BOARD_SIZE) {// for the last iteration
                    Bchecksboard[i - f][j] = 'c';
                }

                int k = 1;
                while (0 <= i + k && i + k < BOARD_SIZE && (board[i + k][j] == ' '|| board[i + k][j] == 'K')) {//down checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i + k][j] = 'c';
                    k++;
                }if (0 <= i + k && i + k < BOARD_SIZE) {
                    Bchecksboard[i + k][j] = 'c';// for the last iteration
                }
                int m = 1;
                while (0 <= j + m && j + m < BOARD_SIZE && (board[i][j + m] == ' '|| board[i][j + m] == 'K')) {//right checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i][j + m] = 'c';
                    m++;

                }if (0 <= j + m && j + m < BOARD_SIZE) {
                    Bchecksboard[i][j + m] = 'c';// for the last iteration
                }

                int x = 1;
                while (0 <= j - x && j - x < BOARD_SIZE && (board[i][j - x] == ' ' || board[i][j - x] == 'K')) {//left checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i][j - x] = 'c';
                    x++;
                }if (0 <= j - x && j - x < BOARD_SIZE) {
                    Bchecksboard[i][j - x] = 'c';// for the last iteration
                }

                int ctr = 1;
                while (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE && (board[i + ctr][j + ctr] == ' ' || board[i + ctr][j + ctr] == 'K')) {//south east checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i + ctr][j + ctr] = 'c';
                    ctr++;
                } if (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE) {
                    Bchecksboard[i + ctr][j + ctr] = 'c';// for the last iteration
                }

                ctr = 1;
                while (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE && (board[i - ctr][j + ctr] == ' ' || board[i - ctr][j + ctr] == 'K')) {//north east checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i - ctr][j + ctr] = 'c';
                    ctr++;
                }if (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE) {
                    Bchecksboard[i - ctr][j + ctr] = 'c';// for the last iteration
                }

                ctr = 1;
                while (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE && (board[i - ctr][j - ctr] == ' ' || board[i - ctr][j - ctr] == 'K')) {//north west checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i - ctr][j - ctr] = 'c';
                    ctr++;
                } if (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE) {
                    Bchecksboard[i - ctr][j - ctr] = 'c';// for the last iteration
                }

                ctr = 1;
                while (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE && (board[i + ctr][j - ctr] == ' ' || board[i + ctr][j - ctr] == 'K')) {//south west checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i + ctr][j - ctr] = 'c';
                    ctr++;
                }if (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE) {
                    Bchecksboard[i + ctr][j - ctr] = 'c';// for the last iteration
                }
            }
            else if (board[i][j] == 'r') {// places the checks done by the rooks on the board
                
                int f = 1;
                while (0 <= i - f && i - f < BOARD_SIZE && (board[i - f][j] == ' ' || board[i - f][j] == 'K')) {//up checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i - f][j] = 'c';
                    f++;
                }if (0 <= i - f && i - f < BOARD_SIZE) {// for the last iteration
                    Bchecksboard[i - f][j] = 'c';
                }

                int k = 1;
                while (0 <= i + k && i + k < BOARD_SIZE && (board[i + k][j] == ' ' || board[i + k][j] == 'K')) {//down checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i + k][j] = 'c';
                    k++;
                }if (0 <= i + k && i + k < BOARD_SIZE) {
                    Bchecksboard[i + k][j] = 'c';// for the last iteration
                }
                int m = 1;
                while (0 <= j + m && j + m < BOARD_SIZE && (board[i][j + m] == ' ' || board[i][j + m] == 'K')) {//right checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i][j + m] = 'c';
                    m++;

                }if (0 <= j + m && j + m < BOARD_SIZE) {
                    Bchecksboard[i][j + m] = 'c';// for the last iteration
                }

                int x = 1;
                while (0 <= j - x && j - x < BOARD_SIZE && (board[i][j - x] == ' ' || board[i][j - x] == 'K')) {//left checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i][j - x] = 'c';
                    x++;
                }if (0 <= j - x && j - x < BOARD_SIZE) {
                    Bchecksboard[i][j - x] = 'c';// for the last iteration
                }
            }
            else if (board[i][j] == 'b') {// places the checks done by the bishop on the board
                int ctr = 1;
                while (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE && (board[i + ctr][j + ctr] == ' ' || board[i + ctr][j + ctr] == 'K')) {//south east checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i + ctr][j + ctr] = 'c';
                    ctr++;
                } if (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE) {
                    Bchecksboard[i + ctr][j + ctr] = 'c';// for the last iteration
                }

                ctr = 1;
                while (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE && (board[i - ctr][j + ctr] == ' ' || board[i - ctr][j + ctr] == 'K')) {//north east checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i - ctr][j + ctr] = 'c';
                    ctr++;
                }if (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE) {
                    Bchecksboard[i - ctr][j + ctr] = 'c';// for the last iteration
                }

                ctr = 1;
                while (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE && (board[i - ctr][j - ctr] == ' ' || board[i - ctr][j - ctr] == 'K')) {//north west checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i - ctr][j - ctr] = 'c';
                    ctr++;
                } if (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE) {
                    Bchecksboard[i - ctr][j - ctr] = 'c';// for the last iteration
                }

                ctr = 1;
                while (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE && (board[i + ctr][j - ctr] == ' ' || board[i + ctr][j - ctr] == 'K')) {//south west checks// i am testing the checks here for the opponents king aswell
                    Bchecksboard[i + ctr][j - ctr] = 'c';
                    ctr++;
                }if (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE) {
                    Bchecksboard[i + ctr][j - ctr] = 'c';// for the last iteration
                }
                }
            else if (board[i][j] == 'n') {// places the checks done by the knight on the board
                if (0 <= i - 2 && i - 2 < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {// up twice once to the right
                    Bchecksboard[i - 2][j + 1] = 'c';
                }
                if (0 <= i - 2 && i - 2 < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {// up twice nce to the left
                    Bchecksboard[i - 2][j - 1] = 'c';
                }
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j - 2 && j - 2 < BOARD_SIZE) {// twice to the left once up
                    Bchecksboard[i - 1][j - 2] = 'c';
                }
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j - 2 && j - 2 < BOARD_SIZE) {// twice to the left once down//
                    Bchecksboard[i + 1][j - 2] = 'c';
                }
                if (0 <= i + 2 && i + 2 < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {// down twice once to the left
                    Bchecksboard[i + 2][j - 1] = 'c';
                }
                if (0 <= i + 2 && i + 2 < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {// down twice once to the right
                    Bchecksboard[i + 2][j + 1] = 'c';
                }
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j + 2 && j + 2 < BOARD_SIZE) {// to the right twice and once down
                    Bchecksboard[i + 1][j + 2] = 'c';
                }
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j + 2 && j + 2 < BOARD_SIZE) {// twice to the right once up
                    Bchecksboard[i - 1][j + 2] = 'c';
                }

            }



        }
    }
}
void updateWchecksboard(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE]) {// places checks done by the white pieces on the board for the white checks
    for (int i = 0; i < BOARD_SIZE;i++) {// initializes the checks board to zero 
        for (int j = 0;j < BOARD_SIZE;j++) {
            Wchecksboard[i][j] = ' ';
        }
    }

    for (int i = 0; i < BOARD_SIZE;i++) {
        for (int j = 0;j < BOARD_SIZE;j++) {

           if (board[i][j] == 'P') {// places the checks done by the pawns on the board
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {
                    Wchecksboard[i - 1][j - 1] = 'c';
                }
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {
                    Wchecksboard[i - 1][j + 1] = 'c';
                }
            }
            else if (board[i][j] == 'K') { // places the checks done by the king on the board
                if (0 <= i && i < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {
                    Wchecksboard[i][j - 1] = 'c';
                }
                if (0 <= i && i < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {
                    Wchecksboard[i][j + 1] = 'c';
                }
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {
                    Wchecksboard[i - 1][j - 1] = 'c';
                }
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {
                    Wchecksboard[i - 1][j + 1] = 'c';
                }
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {
                    Wchecksboard[i + 1][j - 1] = 'c';
                }
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {
                    Wchecksboard[i + 1][j + 1] = 'c';
                }
                if (0 <= i - 1 && i - 1 < BOARD_SIZE && 0 <= j && j < BOARD_SIZE) {
                    Wchecksboard[i - 1][j] = 'c';
                }
                if (0 <= i + 1 && i + 1 < BOARD_SIZE && 0 <= j && j < BOARD_SIZE) {
                    Wchecksboard[i + 1][j] = 'c';
                }

            }
            else if (board[i][j] == 'Q') {// places the checks done by the queen on the board
                bool piechit = false;
                int f = 1;
                while (0 <= i - f && i - f < BOARD_SIZE && (board[i - f][j] == ' ' || board[i - f][j] == 'k')) {//up checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i - f][j] = 'c';
                    f++;
                }if (0 <= i - f && i - f < BOARD_SIZE) {// for the last iteration
                    Wchecksboard[i - f][j] = 'c';
                }

                int k = 1;
                while (0 <= i + k && i + k < BOARD_SIZE && (board[i + k][j] == ' ' || board[i + k][j] == 'k')) {//down checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i + k][j] = 'c';
                    k++;
                }if(0 <= i + k && i + k < BOARD_SIZE){
                Wchecksboard[i + k][j] = 'c';// for the last iteration
                }
                int m = 1;
                while (0 <= j + m && j + m < BOARD_SIZE && (board[i][j+m] == ' ' || board[i][j + m] == 'k')) {//right checks // i am testing the checks here for the opponents king aswell
                    Wchecksboard[i ][j+m] = 'c';
                    m++;
                    
                }if (0 <= j + m && j + m < BOARD_SIZE) {
                    Wchecksboard[i][j + m] = 'c';// for the last iteration
                }
               
                int x = 1;
                while (0 <= j-x && j-x < BOARD_SIZE && (board[i][j-x ] == ' ' || board[i][j - x] == 'k')) {//left checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i][j-x] = 'c';
                    x++;
                }if (0 <= j - x && j - x < BOARD_SIZE) {
                    Wchecksboard[i][j - x] = 'c';// for the last iteration
                }
               
                int ctr = 1;
                while (0 <= j +ctr && j + ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE && (board[i+ctr][j +ctr] == ' ' || board[i + ctr][j + ctr] == 'k')) {//south east checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i+ctr][j +ctr] = 'c';
                    ctr++;
                } if (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE) {
                    Wchecksboard[i + ctr][j + ctr] = 'c';// for the last iteration
                }
               
                ctr  = 1;
                while (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE && (board[i - ctr][j + ctr] == ' ' || board[i - ctr][j + ctr] == 'k')) {//north east checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i - ctr][j + ctr] = 'c';
                    ctr++;
                }if (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE) {
                    Wchecksboard[i - ctr][j + ctr] = 'c';// for the last iteration
                }
               
                ctr = 1;
                while (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE && (board[i - ctr][j - ctr] == ' '|| board[i - ctr][j - ctr] == 'k')) {//north west checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i - ctr][j - ctr] = 'c';// the error thing here should be gone
                    ctr++;
                } if (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE) {
                    Wchecksboard[i - ctr][j - ctr] = 'c';// for the last iteration
                }
               
                ctr = 1;
                while (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE && (board[i + ctr][j - ctr] == ' ' || board[i + ctr][j - ctr] == 'k')) {//south west checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i + ctr][j - ctr] = 'c';
                    ctr++;
                }if (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE) {
                    Wchecksboard[i + ctr][j - ctr] = 'c';// for the last iteration
                }
               

            }
            else if (board[i][j] == 'R') { // places the checks done by the rooks on the board
               bool piechit = false;
               int f = 1;
               while (0 <= i - f && i - f < BOARD_SIZE && (board[i - f][j] == ' ' || board[i - f][j] == 'k')) {//up checks// i am testing the checks here for the opponents king aswell
                   Wchecksboard[i - f][j] = 'c';
                   f++;
               }if (0 <= i - f && i - f < BOARD_SIZE) {// for the last iteration
                   Wchecksboard[i - f][j] = 'c';
               }

               int k = 1;
               while (0 <= i + k && i + k < BOARD_SIZE && (board[i + k][j] == ' ' || board[i + k][j] == 'k')) {//down checks// i am testing the checks here for the opponents king aswell
                   Wchecksboard[i + k][j] = 'c';
                   k++;
               }if (0 <= i + k && i + k < BOARD_SIZE) {
                   Wchecksboard[i + k][j] = 'c';// for the last iteration
               }
               int m = 1;
               while (0 <= j + m && j + m < BOARD_SIZE && (board[i][j + m] == ' ' || board[i][j + m] == 'k')) {//right checks // i am testing the checks here for the opponents king aswell
                   Wchecksboard[i][j + m] = 'c';
                   m++;

               }if (0 <= j + m && j + m < BOARD_SIZE) {
                   Wchecksboard[i][j + m] = 'c';// for the last iteration
               }

               int x = 1;
               while (0 <= j - x && j - x < BOARD_SIZE && (board[i][j - x] == ' ' || board[i][j - x] == 'k')) {//left checks// i am testing the checks here for the opponents king aswell
                   Wchecksboard[i][j - x] = 'c';
                   x++;
               }if (0 <= j - x && j - x < BOARD_SIZE) {
                   Wchecksboard[i][j - x] = 'c';// for the last iteration
               }
            }
            else if (board[i][j] == 'B') { // places the checks done by the bishops on the board
                bool piechit = false;
                int ctr = 1;
                while (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE && (board[i + ctr][j + ctr] == ' ' || board[i + ctr][j + ctr] == 'k')) {//south east checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i + ctr][j + ctr] = 'c';
                    ctr++;
                } if (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE) {
                    Wchecksboard[i + ctr][j + ctr] = 'c';// for the last iteration
                }

                ctr = 1;
                while (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE && (board[i - ctr][j + ctr] == ' ' || board[i - ctr][j + ctr] == 'k')) {//north east checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i - ctr][j + ctr] = 'c';
                    ctr++;
                }if (0 <= j + ctr && j + ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE) {
                    Wchecksboard[i - ctr][j + ctr] = 'c';// for the last iteration
                }

                ctr = 1;
                while (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE && (board[i - ctr][j - ctr] == ' ' || board[i - ctr][j - ctr] == 'k')) {//north west checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i - ctr][j - ctr] = 'c';// the error thing here should be gone
                    ctr++;
                } if (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i - ctr && i - ctr < BOARD_SIZE) {
                    Wchecksboard[i - ctr][j - ctr] = 'c';// for the last iteration
                }

                ctr = 1;
                while (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE && (board[i + ctr][j - ctr] == ' ' || board[i + ctr][j - ctr] == 'k')) {//south west checks// i am testing the checks here for the opponents king aswell
                    Wchecksboard[i + ctr][j - ctr] = 'c';
                    ctr++;
                }if (0 <= j - ctr && j - ctr < BOARD_SIZE && 0 <= i + ctr && i + ctr < BOARD_SIZE) {
                    Wchecksboard[i + ctr][j - ctr] = 'c';// for the last iteration
                }


            }
            else if (board[i][j] == 'N') { // places the checks done by the knight on the board
                if (0<=i - 2 && i-2<BOARD_SIZE && 0<=j + 1 && j+1 <BOARD_SIZE ) {// up twice once to the right
                    Wchecksboard[i - 2][j + 1] = 'c';
                }
                if (0 <= i - 2 && i - 2 < BOARD_SIZE && 0 <= j -1  && j - 1 < BOARD_SIZE) {// up twice nce to the left
                    Wchecksboard[i - 2][j - 1] = 'c';
                }
                if (0 <= i -1  && i - 1 < BOARD_SIZE && 0 <= j -2 && j -2 < BOARD_SIZE) {// twice to the left once up
                    Wchecksboard[i - 1][j -2] = 'c';
                }
                if (0 <= i +1 && i +1 < BOARD_SIZE && 0 <= j -2  && j -2  < BOARD_SIZE) {// twice to the left once down//
                    Wchecksboard[i +1][j -2] = 'c';
                }
                 if (0 <= i + 2 && i + 2 < BOARD_SIZE && 0 <= j - 1 && j - 1 < BOARD_SIZE) {// down twice once to the left
                    Wchecksboard[i + 2][j - 1] = 'c';
                }
                 if (0 <= i + 2 && i + 2 < BOARD_SIZE && 0 <= j + 1 && j + 1 < BOARD_SIZE) {// down twice once to the right
                    Wchecksboard[i + 2][j + 1] = 'c';
                }
                 if (0 <= i +1 && i +1 < BOARD_SIZE && 0 <= j + 2 && j + 2 < BOARD_SIZE) {// to the right twice and once down
                    Wchecksboard[i +1][j + 2] = 'c';
                }
                 if (0 <= i -1  && i - 1 < BOARD_SIZE && 0 <= j + 2 && j + 2 < BOARD_SIZE) {// twice to the right once up
                    Wchecksboard[i - 1][j + 2] = 'c';
                }
                
            }
        }
    }
}
void initializecolorboard(char board[BOARD_SIZE][BOARD_SIZE]) { // initializes the color board at the beginning of the game
    board[0][0] = 'b';//black rook
    board[0][1] = 'b'; // black knight
    board[0][2] = 'b'; //black bishop
    board[0][3] = 'b'; // black queen 
    board[0][4] = 'b';  // Black king
    board[0][5] = 'b';//black bishop
    board[0][6] = 'b'; // black knight
    board[0][7] = 'b';//black rook

    // Initialize black pawns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[1][i] = 'b';  // Black pawn
    }

    // Initialize empty squares
    for (int row = 2; row < 6; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            board[row][col] = ' ';
        }
    }

    // Initialize the white pieces (uppercase)
    board[7][0] = 'w'; // white rook 
    board[7][1] = 'w'; // white knight
    board[7][2] = 'w';// white bishop
    board[7][3] = 'w'; // white queen  
    board[7][4] = 'w';  // White king
    board[7][5] = 'w';  // white bishop
    board[7][6] = 'w'; // white knight
    board[7][7] = 'w';  // white rook 

    // Initialize white pawns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[6][i] = 'w';  // White pawn
    }
   
}

void initializeChessboard(char board[BOARD_SIZE][BOARD_SIZE]) { // initializes the chess board at the beginning of the board 
    // Initialize the pieces on the board
    // 'Q' represents a queen, 'K' represents a king, 'P' represents a pawn
    // ' ' represents an empty square

    // Initialize the black pieces (lowercase)
    board[0][0] = 'r'; //black rook
    board[0][1] = 'n'; // black knight
    board[0][2] = 'b';//black bishop
    board[0][3] = 'q'; // black queen
    board[0][4] = 'k';  // Black king
    board[0][5] = 'b';//black bishop
    board[0][6] = 'n'; // black knight
    board[0][7] = 'r';//black rook

    // Initialize black pawns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[1][i] = 'p';  // Black pawn
    }

    // Initialize empty squares
    for (int row = 2; row < 6; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            board[row][col] = ' ';
        }
    }

    // Initialize the white pieces (uppercase)
    board[7][0] = 'R';  // white rook
    board[7][1] = 'N'; // white knight
    board[7][2] = 'B';// white bishop
    board[7][3] = 'Q'; // white queen
    board[7][4] = 'K';  // White king
    board[7][5] = 'B'; // white bishop
    board[7][6] = 'N';// white knight
    board[7][7] = 'R'; // white rook

    // Initialize white pawns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[6][i] = 'P';  // White pawn
    }
   
}

void displayChessboard(const char board[BOARD_SIZE][BOARD_SIZE]) { // displays the chess board passed to it 
    // Display the chessboard with boxes around each square
    cout << "    ";
    for (int col = 0; col < BOARD_SIZE; ++col) {
        cout << " " << char('a' + col) << "  ";
    }
    cout << endl;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        cout << setw(2) << (8-row) << " ";
        for (int col = 0; col < BOARD_SIZE; ++col) {
            cout << "| " << board[row][col] << " ";
        }
        cout << "|" << endl;
        cout << "   ";
        for (int col = 0; col < BOARD_SIZE; ++col) {
            cout << "+---";
        }
        cout << "+" << endl;
    }
}
void mainmenu() { // prints the option menu
    cout << "to continue playing press 1, press 2 to offer a draw to your opponent or 3 to resign" << endl;
}
bool first1option(char choice1) { //function to resolve if player 1 offers a draw or resigns
    bool result=false;
    if (choice1 == '3') {
        cout << "player 1 has resigned" << endl;
        result=true;

    }
    else if (choice1 == '2') {
        cout << "player 1 is offering a draw, player 2 would you like to accept" << endl;
        cout << "to accept the draw offer enter 1 and to continue playing enter 2" << endl;
        char choice;
        do {
            cin >> choice;
            if (choice == '1') {
                cout << "the game has ended in a draw" << endl;
                result= true;
            }
            else if (choice == '2') {
                cout << "player 2 has rejected the offer" << endl;
                result= false;
            }
            else {
                cout << "please enter either 1 or 2" << endl;
            }
        } while (choice != '1' && choice != '2');
    }

    return result;
}
bool first2option(char choice1) { //function to resolve if player 1 offers a draw or resigns
    bool result = false;
    if (choice1 == '3') {
        cout << "player 2 has resigned" << endl;
        result=true;

    }
    else if (choice1 == '2') {
        cout << "player 2 is offering a draw, player 1 would you like to accept" << endl;
        cout << "to accept the draw offer enter 1 and to continue playing enter 2" << endl;
        char choice;
        do {
            cin >> choice;
            if (choice == '1') {
                cout << "the game has ended in a draw" << endl;
                result= true;
            }
            else if (choice == '2') {
                cout << "player 1 has rejected the offer" << endl;
                result= false;
            }
            else {
                cout << "please enter either 1 or 2" << endl;
            }
        } while (choice != '1' && choice != '2');
    }
    return result;

}
char getboardidentifier(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) { // function to return character stored in board array
    return board[row][col];


}

