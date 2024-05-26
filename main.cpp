#include <iostream>
#include <iomanip>
#include"generalfunctions.h"

using namespace std;


enum Color { WHITE, BLACK }; // making a speccial type of variable for colors of pieces 
enum Type { EMPTY, KING, PAWN, QUEEN ,ROOK ,BISHOP,KNIGHT }; // making a special type of variable for type of pieces 




struct boardbackup {// structure for the board backups
    char movebackup[BOARD_SIZE][BOARD_SIZE] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    int repctr=1;
};
void makemoveWplayer1(char chessboard[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char colorboard[BOARD_SIZE][BOARD_SIZE], int& initialrow, int& initialcol, int& moverow, int& movecol, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]);
void makemoveBplayer2(char chessboard[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char colorboard[BOARD_SIZE][BOARD_SIZE], int& initialrow, int& initialcol, int& moverow, int& movecol, char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]);
void reverseWmove(char board[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char identifier, char movespaceidentifier, char movespacecolor, int& initialrow, int& initialcol, int& moverow, int& movecol,bool properrun, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]);
void reverseBmove(char board[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char identifier, char movespaceidentifier, char movespacecolor, int& initialrow, int& initialcol, int& moverow, int& movecol,bool properrun, char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]);

boardbackup* boardrepcheck(boardbackup *backupptr, char board[BOARD_SIZE][BOARD_SIZE], int& arraysize,bool& isrepeat) { //checks if the same position has been repeated and flags it as a draw 
    bool isidentical;
    int samecounter = 0;
    for (int i = 0;i < arraysize;i++) {
        isidentical = true;
        for (int k = 0;k < BOARD_SIZE;k++) {// checks if the boards are the same and increments a counter which is related to each board in the structure
            for (int j = 0;j < BOARD_SIZE;j++) {
                if (board[k][j] != backupptr[i].movebackup[k][j]) {
                    isidentical = false;
                }
            }
        }
        if (isidentical == true) {
            backupptr[i].repctr++;
            samecounter++;// increments a counter which will be zero only if the board is not equal to any other boards on the backup
        }
        
    }
    if (samecounter == 0) {
        boardbackup* newbackupptr = new boardbackup[arraysize + 1];
        for (int i = 0;i < arraysize;i++) {//creates a new array with a bigger size by 1 and adds the boards to it from the old array
            for (int k = 0;k < BOARD_SIZE;k++) {
                for (int j = 0;j < BOARD_SIZE;j++) {
                    newbackupptr[i].movebackup[k][j] = backupptr[i].movebackup[k][j];
                }
            }
        }
        for (int i = 0;i < BOARD_SIZE;i++) {
            for (int j = 0;j < BOARD_SIZE;j++) {
                newbackupptr[arraysize].movebackup[i][j] = board[i][j];// adds the last board repition to the end
            }
        }
        delete[] backupptr;//deallocates the old array 
        return newbackupptr;// returns the new array
    }
    else {
        for (int i = 0;i < arraysize;i++) {//changes the result as true if 3 boards are equal 
            if (backupptr[i].repctr == 3) {
                isrepeat = true;
            }
        }
    }
    
    
    return backupptr;
}




class whiteQueen {
private:
    Color color;
    Type type;
    char identifier;
public:
    whiteQueen() {
        color = WHITE;
        type = QUEEN;
        identifier = 'Q';
    }
    static void validateWQueen(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Wcheck, bool properrun, bool& isvalid, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        bool piecehit=false;
        char movespaceidentifier, movespacecolor;
        bool ischeck;
        int rowdiff, coldiff;
        rowdiff = moverow - initialrow; // gets difference for initial and final row 
        coldiff = movecol - initialcol;// gets difference for initial and final column
        if (initialrow == moverow) {// this does movement to the left and right 
            if (initialcol < movecol) {//moving to the right 
                for (int j = initialcol+1;j < movecol;j++) {
                    if (board[initialrow][j] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (initialcol > movecol) {//moving to the left 
                for (int j = initialcol-1;j > movecol;j--) {
                    if (board[initialrow][j] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (Cboard[moverow][movecol] == 'w'){ // Check if the destination space is occupied by a white piece
                piecehit = true;
            }
            
            if (piecehit == false) { // if not ppiece has been hit 
                movespaceidentifier = board[moverow][movecol]; 
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'w';
                isvalid = true;
                // the lines before this will make the move to the desired square 
                updateBchecksboard(board, Bchecksboard);
                ischeck=checkforWcheck(board, Bchecksboard, properrun); // checking for check on the white king 
               
                if (ischeck) { // if the king is checked reverse the move and assign invalid to the move 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun,Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                    isvalid = false;
                }
                if (properrun == false) { // if properrun is false reverse the move, this is for checkmating/ stalemate function 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                }

            }
            
            
        } else if (initialcol == movecol) {// this does movement up and down 
            if (initialrow < moverow) {//moving down
                for (int i = initialrow + 1;i < moverow;i++) {
                    if (board[i][initialcol] != ' ') {
                        piecehit = true;
                    }
                }
            }if (initialrow > moverow) {//moving up
                for (int i = initialrow - 1;i > moverow;i--) {
                    if (board[i][initialcol] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (Cboard[moverow][movecol] == 'w') { // if the square you are moving to has a white piece on it you have hit a piece 
                piecehit = true;
            }
            
            if (piecehit == false) { // if no piece has been hit 
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'w';
                isvalid = true;
                // thie lines before this make the desired move on the board and color board 
                updateBchecksboard(board, Bchecksboard);
                ischeck = checkforWcheck(board, Bchecksboard, properrun); // checks if the white king is in check 
             
                if (ischeck) { // if the king is under check reverse the move and assign false to valid move 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                    isvalid = false;
                }
                if (properrun == false) { // if it is not a properrun reverse the move and update the checks board
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                }

            }


        }
        else if (abs(rowdiff) == abs(coldiff)) {//movement on diagonals
            if (rowdiff > 0 && coldiff > 0) {// south east 
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow+i][initialcol+i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (rowdiff <0  && coldiff > 0) {// north east 
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow - i][initialcol + i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (rowdiff < 0 && coldiff < 0) {// north west
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow - i][initialcol - i] != ' ') {
                        piecehit = true;
                    }
                }
            }if (rowdiff > 0 && coldiff < 0) {// south west
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow + i][initialcol - i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (Cboard[moverow][movecol] == 'w') { //  a piece is hit if the desired movesquare contains a white piece 
                piecehit = true;
            }
            if (piecehit == false) { // if no piece has been hit 
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'w';
                isvalid = true;
                // the lines before this do the move on the board and color board to the desired square 
                updateBchecksboard(board, Bchecksboard);
                ischeck = checkforWcheck(board, Bchecksboard, properrun); // checks if the white king is under check
              
                if (ischeck) { // if the white king is under check reverse the move and assign false to valid move 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                    isvalid = false;
                }
                if (properrun == false) { // if properrun is false then reverse the move 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                }

            }


        }
        else if (properrun == true) { // if properrun is true and none of the past if functions have been entered then flag the move as invalid
            cout << "the move is invalid" << endl;
            makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol,Wpreviousboard);
        }
        
        if (properrun == true && piecehit==true) { // if piecehit is true and it is a properrun then flag the omve as invalid 
            cout << "the move is invalid" << endl;
            makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol,Wpreviousboard);
        }
        
        
        
        
   
    }
 
    

};
class whiteBishop {
private:
    Color color;
    Type type;
    char identifier;
public:
    whiteBishop() {
        color = WHITE;
        type = BISHOP;
        identifier = 'B';
    }
    static void validateWBishop(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Wcheck, bool properrun, bool& isvalid, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        bool piecehit = false;
        char movespaceidentifier, movespacecolor;
        bool ischeck;
        int rowdiff, coldiff;
        rowdiff = moverow - initialrow; 
        coldiff = movecol - initialcol;
         if (abs(rowdiff) == abs(coldiff)) {//movement on diagonals
            if (rowdiff > 0 && coldiff > 0) {// south east 
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow + i][initialcol + i] != ' ' ) {
                        piecehit = true;
                    }

                }
            }
            if (rowdiff < 0 && coldiff > 0) {// north east 
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow - i][initialcol + i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (rowdiff < 0 && coldiff < 0) {// north west
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow - i][initialcol - i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (rowdiff > 0 && coldiff < 0) {// south west
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow + i][initialcol - i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (Cboard[moverow][movecol] == 'w') { // a piece is hit if there is a white piece at the desired move square 
                piecehit = true;
            }
            if (piecehit == false) { // if the piece hit is false 
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'w';
                isvalid = true;
                // the lines before this do the move for the white pieces on both the board and the color board 
                updateBchecksboard(board, Bchecksboard);
                ischeck = checkforWcheck(board, Bchecksboard, properrun); // checks if the white king is under check 

                if (ischeck) { // if the king is under check then it reverses the move and assigns the move as invalid
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                    isvalid = false;
                }
                if (properrun == false) { // if the run is not proper then reverse the move 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                }

            }


        }
        else if (properrun == true) {// else if the run is proper then th move is invalid 
            cout << "the move is invalid" << endl;
            makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Wpreviousboard);
        }

        if (properrun == true && piecehit == true) {// if the run is proper and a piece has been hit then the move is invalid
            cout << "the move is invalid" << endl;
            makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Wpreviousboard);
        }





    }



};
class whiteRook {
private:
    Color color;
    Type type;
    char identifier;
public:
    whiteRook() {
        color = WHITE;
        type = ROOK;
        identifier = 'R';
    }
    static void validateWRook(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Wcheck, bool properrun, bool& isvalid, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        bool piecehit = false;
        char movespaceidentifier, movespacecolor;
        bool ischeck;
     
        if (initialrow == moverow) {// this does movement to the left and right 
            if (initialcol < movecol) {//moving to the right 
                for (int j = initialcol + 1;j < movecol;j++) {
                    if (board[initialrow][j] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (initialcol > movecol) {//moving to the left 
                for (int j = initialcol - 1;j > movecol;j--) {
                    if (board[initialrow][j] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (Cboard[moverow][movecol] == 'w') { // a piece is hit if there is a white ppiece on the desired move square 
                piecehit = true;
            }

            if (piecehit == false) { // if no piece has been hit 
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'w';
                isvalid = true;
                // the lines before this do the movement for the white piece to the square on both the board and dcolor board 
                updateBchecksboard(board, Bchecksboard);
                ischeck = checkforWcheck(board, Bchecksboard, properrun); // checks if the white king is under check

                if (ischeck) { // reverses the move and assigns invalid to the move if the king is under check 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                    isvalid = false;
                }
                if (properrun == false) { // if the run is not proper the move is reversed 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                }

            }


        }
        else if (initialcol == movecol) {// this does movement up and down 
            if (initialrow < moverow) {//moving down
                for (int i = initialrow + 1;i < moverow;i++) {
                    if (board[i][initialcol] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (initialrow > moverow) {//moving up
                for (int i = initialrow - 1;i > moverow;i--) {
                    if (board[i][initialcol] != ' ') {
                        piecehit = true;
                    }
                }
            }if (Cboard[moverow][movecol] == 'w') {// a piece is hit if there is a white ppiece on the desired move square 
                piecehit = true;
            }

            if (piecehit == false) {
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'w';
                isvalid = true;
                // the lines before this do the movement for the white piece to the square on both the board and dcolor board
                updateBchecksboard(board, Bchecksboard);
                ischeck = checkforWcheck(board, Bchecksboard, properrun);// checks if the white king is under check

                if (ischeck) {// reverses the move and assigns invalid to the move if the king is under check 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                    isvalid = false;
                }
                if (properrun == false) {// if the run is not proper the move is reversed 
                    reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                    updateBchecksboard(board, Bchecksboard);
                }

            }


        }
        else if (properrun == true) {// reverses the move and assigns invalid to the move if the king is under check 
            cout << "the move is invalid" << endl;
            makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Wpreviousboard);
        }

        if (properrun == true && piecehit == true) {// if the run is not proper the move is reversed 
            cout << "the move is invalid" << endl;
            makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Wpreviousboard);
        }





    }



};
class whiteKnight {
private:
    Color color;
    Type type;
    char identifier;
public:
    whiteKnight() {
        type = KNIGHT;
        color = WHITE;
        identifier = 'N'; 
    }
    static void validateWKnight(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Wcheck, bool properrun, bool& isvalid, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        char movespaceidentifier, movespacecolor;
        bool ischeck;
        if (initialrow - 2 == moverow && initialcol +1 == movecol && Cboard[moverow][movecol] != 'w' ) {// up twice nce to the right 
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            // the lines before this do the move for the white pieces 
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard, properrun); // checks if the white is  under check 

            if (ischeck) { // reverses the move and assigns the move a invslid if the king is under check 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) { // if the run is not proper then the move is reversed 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }else if (initialrow - 2 == moverow && initialcol - 1 == movecol && Cboard[moverow][movecol] != 'w') { //up twice once to the left
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            // Move the knight to the destination space
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard, properrun);

            // If the move results in the white king being in check
            if (ischeck) {
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            // If the move is part of a proper run
            if (properrun == false) {
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol -2 == movecol && Cboard[moverow][movecol] != 'w') {//twice to the left once up
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            //moves the knight to the intended space 
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard, properrun); // checks if white king is under check 

            if (ischeck) {// if the white king is under check reverse the move and assign false to the move 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) { // if properrun is false then reverse the move 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow +1 == moverow && initialcol -2 == movecol && Cboard[moverow][movecol] != 'w') {//twice to the left once down 
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            // the lines before this move the knight to the intended position on both color board and chessboard
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard, properrun);//checks if the white king is under check 

            if (ischeck) { // if the white king is under check then reverse the move and assign false to this move being valid
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// revreses the move if the run is not proper 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow + 2 == moverow && initialcol - 1 == movecol && Cboard[moverow][movecol] != 'w') {//twice down once to the left
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            // the lines before this will move the knight to the intended square 
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard, properrun);// checks if the white king is under check after making the move 

            if (ischeck) {// if the white king is under check then the move is reversed and false is assigned to the move being valid 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// reverses the move if the move is not proper 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow + 2 == moverow && initialcol + 1 == movecol && Cboard[moverow][movecol] != 'w') {//twice down once to the right 
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            //move the knight ot the intended square 
            isvalid = true;
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard, properrun);// checks if the white king is under check 

            if (ischeck) {// if the white king is under check then the move is reversed and flase is assigned to the move being valid 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// the move is reversed if the move is not proper 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
            }
        else if (initialrow +1 == moverow && initialcol + 2 == movecol && Cboard[moverow][movecol] != 'w') {//twice to the right once down
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            // the lines bbefore this move the knight to the intended square 
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard, properrun);//checks if the white king is under check 

            if (ischeck) {// the move is reversed if the white king is under check and false is assigned to the move being valid 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) { // the move is reversed if the properrun is false 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
            }
        else if (initialrow -1 == moverow && initialcol + 2 == movecol && Cboard[moverow][movecol] != 'w') { //twice to the right once up
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            // the lines before this move the knight to the intended square 
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard, properrun);// checks if the white king is under check

            if (ischeck) {// if the white king is checked then reverse the move and assign false to the mve being valid 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) { // reverse the move if the run is not proper 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
            }
        
        else if (properrun == true) { // if the proper run is true and none of the if statements are satisfied then the move is invalid and ask the player to move again 
            cout << "the move is invalid" << endl;
            makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Wpreviousboard);
        }
    }
};

class whiteKing {
private:
    Color color;
    Type type;
    char identifier;
    int colposition;
    int rowposition;
public:
    whiteKing() {
        type = KING;
        color = WHITE;
        identifier = 'K';
        colposition = 4;
        rowposition = 7;
    }
    static void validateWking(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Wcheck,bool properrun,bool& isvalid, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        char movespaceidentifier, movespacecolor;
        
        if (initialrow == moverow && initialcol == movecol - 1 && Cboard[moverow][movecol] != 'w' && Bchecksboard[moverow][movecol] != 'c') {//moves to the left
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            //the lines before this are moving the king to the inended square 
            if (properrun == false) {// if the run is not proper reverse the move
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow == moverow && initialcol == movecol + 1 && Cboard[moverow][movecol] != 'w' && Bchecksboard[moverow][movecol] != 'c') {// moves to the right 
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            isvalid = true;
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            //the lines before this are moving the king to the inended square on both board the color board and chessboard
            if (properrun == false) {// if the run is not proper reverse the move
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol == movecol && Cboard[moverow][movecol] != 'w' && Bchecksboard[moverow][movecol] != 'c') {//moves north
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            isvalid = true;
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            //the lines before this are moving the king to the inended square on both board the color board and chessboard
            if (properrun == false) {// if the run is not proper reverse the move
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol - 1 == movecol && Cboard[moverow][movecol] != 'w' && Bchecksboard[moverow][movecol] != 'c') {//moves north west
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            isvalid = true;
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            //the lines before this are moving the king to the inended square on both board the color board and chessboard
            if (properrun == false) {// if the run is not proper reverse the move
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol + 1 == movecol && Cboard[moverow][movecol] != 'w' && Bchecksboard[moverow][movecol] != 'c') {//moves north east
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            isvalid = true;
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            //the lines before this are moving the king to the inended square on both board the color board and chessboard
            if (properrun == false) {// if the run is not proper reverse the move
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol == movecol && Cboard[moverow][movecol] != 'w' && Bchecksboard[moverow][movecol] != 'c') {//moves south
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            isvalid = true;
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            //the lines before this are moving the king to the inended square on both board the color board and chessboard
            if (properrun == false) {// if the run is not proper reverse the move
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol - 1 == movecol && Cboard[moverow][movecol] != 'w' && Bchecksboard[moverow][movecol] != 'c') {//moves south west
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            isvalid = true;
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            //the lines before this are moving the king to the inended square on both board the color board and chessboard
            if (properrun == false) {// if the run is not proper reverse the move
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol + 1 == movecol && Cboard[moverow][movecol] != 'w' && Bchecksboard[moverow][movecol] != 'c') {//moves south east
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            isvalid = true;
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            //the lines before this are moving the king to the inended square on both board the color board and chessboard
            if (properrun == false) {// if the run is not proper reverse the move
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (properrun==true){// if the proper run is true and none of the if statements are satisfied then the move is invalid and ask the player to make a move 
            cout << "the move is invalid" << endl;
            makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Wpreviousboard);
        }
    }
};

class whitePawn {
private:
    Color color;
    Type type;
    char identifier;
public:
    whitePawn() {
        type = PAWN;
        color = WHITE;
        identifier = 'P';

    }
    static void validateWpawn(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Wcheck,bool properrun,bool&isvalid, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        char movespaceidentifier, movespacecolor;
        bool ischeck;
        if (initialrow == 6 && initialrow - 2 == moverow && initialcol == movecol && board[moverow][movecol] == ' ' && board[moverow + 1][movecol] == ' ') {
            //the special 2 squares first move for a pawn
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            //the lines before this move the piece to the intended square 
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard,properrun); // checks if the white king is under check 
            if (ischeck) {// if the white king is checked then reverse the move and assign false to the being being valid 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol,properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// revesrses the move is the properrun is false 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }

        }
        else if (initialrow - 1 == moverow && initialcol + 1 == movecol && board[moverow][movecol] == ' ' && board[moverow + 1][movecol] == 'p' && initialrow==3 && Wpreviousboard[initialrow-2][initialcol+1]=='p' && Wpreviousboard[initialrow][initialcol + 1] == ' ') {
            movespaceidentifier = board[moverow + 1][movecol];//special move so will require different reversing methods
            movespacecolor = Cboard[moverow + 1][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            board[moverow + 1][movecol] = ' '; //en passant first side 
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            //lines before this move pawn to intended square
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard,properrun);// check if white king is under check after making the move 
            if (ischeck == true) {// if the king is checked then the move is reversed nd the move is flagged as invalid 
                board[initialrow][initialcol] = identifier;
                board[moverow][movecol] = ' ';
                board[moverow + 1][movecol] = movespaceidentifier;
                Cboard[initialrow][initialcol] = 'w';
                Cboard[moverow][movecol] = ' ';
                Cboard[moverow + 1][movecol] = movespacecolor;
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
                if (properrun == true) {
                    cout << "cannot make that move as the king will be in heck after making the move" << endl;
                }
            }
            if (properrun == false) {//reverses the move if the run is not proper 
                board[initialrow][initialcol] = identifier;
                board[moverow][movecol] = ' ';
                board[moverow + 1][movecol] = movespaceidentifier;
                Cboard[initialrow][initialcol] = 'w';
                Cboard[moverow][movecol] = ' ';
                Cboard[moverow + 1][movecol] = movespacecolor;
                updateBchecksboard(board, Bchecksboard);
            }

        }
        else if (initialrow - 1 == moverow && initialcol - 1 == movecol && board[moverow][movecol] == ' ' && board[moverow + 1][movecol] == 'p' && initialrow == 3 && Wpreviousboard[initialrow - 2][initialcol -1] == 'p' && Wpreviousboard[initialrow][initialcol - 1] == ' ') {
            movespaceidentifier = board[moverow + 1][movecol];//special move so will require different reversing methods
            movespacecolor = Cboard[moverow + 1][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            board[moverow + 1][movecol] = ' '; //en passant second side 
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            //lines before this will move the pawn to the intended square 
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard,properrun);// checks if the white king is under check after making the move 
            if (ischeck == true) {// if the king is checked then the move is reversed and false is assigned to the move being valid 
                board[initialrow][initialcol] = identifier;
                board[moverow][movecol] = ' ';
                board[moverow + 1][movecol] = movespaceidentifier;
                Cboard[initialrow][initialcol] = 'w';
                Cboard[moverow][movecol] = ' ';
                Cboard[moverow + 1][movecol] = movespacecolor;
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
                if (properrun == true) {
                    cout << "cannot make that move as the king will be in check after making the move" << endl;
                }
               
            }
            if (properrun == false) {// move is reversed if it is not a properrun
                board[initialrow][initialcol] = identifier;
                board[moverow][movecol] = ' ';
                board[moverow + 1][movecol] = movespaceidentifier;
                Cboard[initialrow][initialcol] = 'w';
                Cboard[moverow][movecol] = ' ';
                Cboard[moverow + 1][movecol] = movespacecolor;
                updateBchecksboard(board, Bchecksboard);
            }
            
        }
        else  if (initialrow - 1 == moverow && initialcol == movecol && board[moverow][movecol] == ' ') {
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';

            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';

            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            // the lines before this will move the pawn to the intended square
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard,properrun);//checks if the white king is under check 
            if (ischeck) {//if the king is checked thenn the move is reversed and flagged as invalid 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol,properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) {//if the run is not proper then the move is reversed 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol == movecol - 1 && Cboard[moverow][movecol] == 'b') {
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';

            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';

            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            //the lines before this will move the pawn to the intended square 
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard,properrun);//checks if the white king is under check after making the move 
            if (ischeck) {//if the hite king is checked then the move is reversed and false is assigned to the move being valid 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol,properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }

        }
        else if (initialrow - 1 == moverow && initialcol == movecol + 1 && Cboard[moverow][movecol] == 'b') {
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';

            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';

            Cboard[moverow][movecol] = 'w';
            isvalid = true;
            // the lines before this move the pawn to the intended square 
            updateBchecksboard(board, Bchecksboard);
            ischeck = checkforWcheck(board, Bchecksboard,properrun);// checks if the white king is under check after making the move 
            if (ischeck) {// if the king is checked then the move is reversed and the 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol,properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseWmove(board, Cboard, Bchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Wpreviousboard);
                updateBchecksboard(board, Bchecksboard);
            }
        }
        else if(properrun==true) {// if the proper run is true and none of the other if statements are satisfied then the move is invalid nd the user is asked to make a new move
            cout << "the move is invalid" << endl;
            makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Wpreviousboard);
        }
    }


};
class blackQueen {
private:
    Color color;
    Type type;
    char identifier;
public:
    blackQueen() {
        color = WHITE;
        type = QUEEN;
        identifier = 'q';
    }
    static void validateBQueen(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Bcheck, bool properrun, bool& isvalid, char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        bool piecehit = false;
        char movespaceidentifier, movespacecolor;
        bool ischeck;
        int rowdiff, coldiff;
        rowdiff = moverow - initialrow;
        coldiff = movecol - initialcol;
        if (initialrow == moverow) {// this does movement to the left and right 
            if (initialcol < movecol) {//moving to the right 
                for (int j = initialcol + 1;j < movecol;j++) {
                    if (board[initialrow][j] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (initialcol > movecol) {//moving to the left 
                for (int j = initialcol - 1;j > movecol;j--) {
                    if (board[initialrow][j] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (Cboard[moverow][movecol] == 'b') { // piece is hit if there is a black piece where you want to move 
                piecehit = true;
            }

            if (piecehit == false) { // if a piece is not hit 
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'b';
                isvalid = true;
                //the lines before this move the piece on both the board and color board
                updateWchecksboard(board, Wchecksboard);
                ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks if the black king is under check 
       
                if (ischeck) {//if the king is under check reverse the move and assign false to the move being valid 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                    isvalid = false;
                }
                if (properrun == false) { // if the run is not proper reverse the move 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                }

            }


        }
        else if (initialcol == movecol) {// this does movement up and down 
            if (initialrow < moverow) {//moving down
                for (int i = initialrow + 1;i < moverow;i++) {
                    if (board[i][initialcol] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (initialrow > moverow) {//moving up
                for (int i = initialrow - 1;i > moverow;i--) {
                    if (board[i][initialcol] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (Cboard[moverow][movecol] == 'b') { // a piece is hit if there is a black piece where we want ot move 
                piecehit = true;
            }

            if (piecehit == false) { // if no piece is hit
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'b';
                isvalid = true;
                // the lines before this make the move on the both chessboard and color board  
                updateWchecksboard(board, Wchecksboard);
                ischeck = checkforBcheck(board, Wchecksboard, properrun); // check if the black king is under check 
         
                if (ischeck) {// if the black king is under check reverse the move and assign false ot the move
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                    isvalid = false;
                }
                if (properrun == false) { // if the run is false reverse the move
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                }

            }


        }
        else if (abs(rowdiff) == abs(coldiff)) {//movement on diagonals
            if (rowdiff > 0 && coldiff > 0) {// south east 
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow + i][initialcol + i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (rowdiff < 0 && coldiff > 0) {// north east 
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow - i][initialcol + i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (rowdiff < 0 && coldiff < 0) {// north west
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow - i][initialcol - i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (rowdiff > 0 && coldiff < 0) {// south west
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow + i][initialcol - i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (Cboard[moverow][movecol] == 'b') { // piece is hit if there is a black piece where we want to move
                piecehit = true;
            }
            if (piecehit == false) { // if no piece is hit 
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'b';
                isvalid = true;
                // the lines before this move the piece on both chesscoard and color board 
                updateWchecksboard(board, Wchecksboard);
                ischeck = checkforBcheck(board, Wchecksboard, properrun); // checks for a check on the black king 
         
                if (ischeck) {// if the king is checked reverse the move and assign the move as invalid 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                    isvalid = false;
                }
                if (properrun == false) {// if the run is not proper reverse the move 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                }

            }


        }
        else if (properrun == true) { // if the run is proper and none of the other if statements are satisfied then the move is invalid and ask the player to make another move 
            cout << "the move is invalid" << endl;
            makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
        }

        if (properrun == true && piecehit == true) {// if the run is proper and a piece has been hit then the move is invalid and ask the player to make another move 
            cout << "the move is invalid" << endl;
            makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
        }





    }



};
class blackBishop {
private:
    Color color;
    Type type;
    char identifier;
public:
    blackBishop() {
        color = WHITE;
        type = BISHOP;
        identifier = 'b';
    }
    static void validateBBishop(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Bcheck, bool properrun, bool& isvalid, char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        bool piecehit = false;
        char movespaceidentifier, movespacecolor;
        bool ischeck;
        int rowdiff, coldiff;
        rowdiff = moverow - initialrow;
        coldiff = movecol - initialcol;
        
        if (abs(rowdiff) == abs(coldiff)) {//movement on diagonals
            if (rowdiff > 0 && coldiff > 0) {// south east 
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow + i][initialcol + i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (rowdiff < 0 && coldiff > 0) {// north east 
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow - i][initialcol + i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }
            if (rowdiff < 0 && coldiff < 0) {// north west
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow - i][initialcol - i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (rowdiff > 0 && coldiff < 0) {// south west
                for (int i = 1;i < abs(rowdiff);i++) {
                    if (board[initialrow + i][initialcol - i] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (Cboard[moverow][movecol] == 'b') {// a piece has been hit if there is a black piece where we want to move 
                piecehit = true;
            }
            if (piecehit == false) { // if no piece has been hit 
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'b';
                isvalid = true;
                // the lines before this move the piece on both the chessboard and the colorboard
                updateWchecksboard(board, Wchecksboard);
                ischeck = checkforBcheck(board, Wchecksboard, properrun); // checks for a check on the black pieces 

                if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                    isvalid = false;
                }
                if (properrun == false) {// if the run is not proper then the move is reversed 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                }

            }


        }
        else if (properrun == true) {// if the run is proper and none of the if statements have been satisfied then the move is invalid and ask the player to make another move 
            cout << "the move is invalid" << endl;
            makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
        }

        if (properrun == true && piecehit == true) {// if a piece has been hit and the run is proper then the move is invalid and ask the user for a new move
            cout << "the move is invalid" << endl;
            makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
        }





    }



};
class blackRook {
private:
    Color color;
    Type type;
    char identifier;
public:
    blackRook() {
        color = WHITE;
        type = ROOK;
        identifier = 'r';
    }
    static void validateBRook(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Bcheck, bool properrun, bool& isvalid, char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        bool piecehit = false;
        char movespaceidentifier, movespacecolor;
        bool ischeck;
       
        if (initialrow == moverow) {// this does movement to the left and right 
            if (initialcol < movecol) {//moving to the right 
                for (int j = initialcol + 1;j < movecol;j++) {
                    if (board[initialrow][j] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (initialcol > movecol) {//moving to the left 
                for (int j = initialcol - 1;j > movecol;j--) {
                    if (board[initialrow][j] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (Cboard[moverow][movecol] == 'b') {// a piece has been hit if there is a black piece where we want to move 
                piecehit = true;
            }

            if (piecehit == false) {
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'b';
                isvalid = true;
                // the lines before this move the piece on both the chessboard and the colorboard
                updateWchecksboard(board, Wchecksboard);
                ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

                if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                    isvalid = false;
                }
                if (properrun == false) {// if the run is not proper then the move is reversed 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                }

            }


        }
        else if (initialcol == movecol) {// this does movement up and down 
            if (initialrow < moverow) {//moving down
                for (int i = initialrow + 1;i < moverow;i++) {
                    if (board[i][initialcol] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (initialrow > moverow) {//moving up
                for (int i = initialrow - 1;i > moverow;i--) {
                    if (board[i][initialcol] != ' ' ) {
                        piecehit = true;
                    }
                }
            }if (Cboard[moverow][movecol] == 'b') {// a piece has been hit if there is a black piece where we want to move
                piecehit = true;
            }

            if (piecehit == false) {
                movespaceidentifier = board[moverow][movecol];
                movespacecolor = Cboard[moverow][movecol];
                board[initialrow][initialcol] = ' ';
                board[moverow][movecol] = identifier;
                Cboard[initialrow][initialcol] = ' ';
                Cboard[moverow][movecol] = 'b';
                isvalid = true;
                // the lines before this move the piece on both the chessboard and the colorboard
                updateWchecksboard(board, Wchecksboard);
                ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

                if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                    isvalid = false;
                }
                if (properrun == false) {// if the run is not proper then the move is reversed 
                    reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                    updateWchecksboard(board, Wchecksboard);
                }

            }


        }
        else if (properrun == true) {// if the run is proper and none of the if statements have been satisfied then the move is invalid and ask the player to make another move 
            cout << "the move is invalid" << endl;
            makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
        }

        if (properrun == true && piecehit == true) {// if a piece has been hit and the run is proper then the move is invalid and ask the user for a new move
            cout << "the move is invalid" << endl;
            makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
        }





    }



};
class blackKnight {
private:
    Color color;
    Type type;
    char identifier;
public:
    blackKnight() {
        type = KNIGHT;
        color = WHITE;
        identifier = 'n';
    }
    static void validateBKnight(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Wcheck, bool properrun, bool& isvalid, char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        char movespaceidentifier, movespacecolor;
        bool ischeck;
        if (initialrow - 2 == moverow && initialcol + 1 == movecol && Cboard[moverow][movecol] != 'b') {// up twice once to the right 
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

            if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow - 2 == moverow && initialcol - 1 == movecol && Cboard[moverow][movecol] != 'b') { //up twice once to the left
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

            if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol - 2 == movecol && Cboard[moverow][movecol] != 'b') {//twice to the left once up
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

            if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol - 2 == movecol && Cboard[moverow][movecol] != 'b') {//twice to the left once down 
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

            if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 2 == moverow && initialcol - 1 == movecol && Cboard[moverow][movecol] != 'b') {//twice down once to the left
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

            if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 2 == moverow && initialcol + 1 == movecol && Cboard[moverow][movecol] != 'b') {//twice down once to the right 
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

            if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol + 2 == movecol && Cboard[moverow][movecol] != 'b') {//twice to the right once down
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

            if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol + 2 == movecol && Cboard[moverow][movecol] != 'b') { //twice to the right once up
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard, properrun);// checks for a check on the black pieces 

            if (ischeck) {// if the king is under check reverse the move and assign the move as invalid 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper then the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }

        else if (properrun == true) {// if the run is proper and none of the if statements have been satisfied then the move is invalid and ask the player to make another move 
            cout << "the move is invalid" << endl;
            makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
        }
    }
};
class blackKing {
private:
    Color color;
    Type type;
    char identifier;
    int colposition;
    int rowposition;
public:
    blackKing() {
        type = KING;
        color = BLACK;
        identifier = 'k';
        colposition = 4;
        rowposition = 7;
    }
    static void validateBking(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Bcheck,bool properrun, bool& isvalid, char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        char movespaceidentifier, movespacecolor;
        if (initialrow == moverow && initialcol == movecol - 1 && Cboard[moverow][movecol] != 'b' && Wchecksboard[moverow][movecol] != 'c') {//moves to the left
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            if (properrun == false) {
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow == moverow && initialcol == movecol + 1 && Cboard[moverow][movecol] != 'b' && Wchecksboard[moverow][movecol] != 'c') { // moves to the right
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            if (properrun == false) {
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol == movecol && Cboard[moverow][movecol] != 'b' && Wchecksboard[moverow][movecol] != 'c') {//moves north
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            if (properrun == false) {
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol - 1 == movecol && Cboard[moverow][movecol] != 'b' && Wchecksboard[moverow][movecol] != 'c') {//moves north west
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            if (properrun == false) {
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow - 1 == moverow && initialcol + 1 == movecol && Cboard[moverow][movecol] != 'b' && Wchecksboard[moverow][movecol] != 'c') {//moves north east
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            if (properrun == false) {
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol == movecol && Cboard[moverow][movecol] != 'b' && Wchecksboard[moverow][movecol] != 'c') {//moves south
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            if (properrun == false) {
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol - 1 == movecol && Cboard[moverow][movecol] != 'b' && Wchecksboard[moverow][movecol] != 'c') {//moves south west
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            if (properrun == false) {
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol + 1 == movecol && Cboard[moverow][movecol] != 'b' && Wchecksboard[moverow][movecol] != 'c') {// moves south east
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this move the piece on both the chessboard and the colorboard
            if (properrun == false) {
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (properrun == true) {// if the run is proper and none of the if functions have been satisfied then the move is invalid and the user is asked to make another move
             
                cout << "the move is invalid" << endl;
                makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
            
           
        }
    }
};
class blackPawn {
private:
    Color color;
    Type type;
    char identifier;
public:
    blackPawn() {
        type = PAWN;
        color = BLACK;
        identifier = 'p';

    }
    static void validateBpawn(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], int initialrow, int initialcol, int moverow, int movecol, char identifier, bool& Bcheck,bool properrun,bool& isvalid, char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
        char movespaceidentifier, movespacecolor;
        bool ischeck;
        if (initialrow == 1 && initialrow + 2 == moverow && initialcol == movecol && board[moverow][movecol] == ' ' && board[moverow - 1][movecol] == ' ') {//special 2 square move forward 
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            //the special 2 squares first move for a pawn
            board[initialrow][initialcol] = ' ';

            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';

            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this do the move on both the chessboard and the color board
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard,properrun);// check if the black king is checked 
            if (ischeck) {// if the king is checked then reverse the move and flag the move as invalid
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol,properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }
            if (properrun == false) {// if the run is not proper the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol + 1 == movecol && board[moverow][movecol] == ' ' && board[moverow - 1][movecol] == 'P' && initialrow == 4 && Bpreviousboard[initialrow + 2][initialcol + 1] == 'P' && Bpreviousboard[initialrow][initialcol + 1] == ' ') {//en passant 
            movespaceidentifier = board[moverow - 1][movecol];//special move so will require different reversing methods
            movespacecolor = Cboard[moverow - 1][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            board[moverow - 1][movecol] = ' '; //en passant first side
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this do the move on both the chessboard and the color board
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard,properrun);// check if the black king is checked 
            if (ischeck == true) {// if the king is checked then reverse the move and flag the move as invalid
                board[initialrow][initialcol] = identifier;
                board[moverow][movecol] = ' ';
                board[moverow - 1][movecol] = movespaceidentifier;
                Cboard[initialrow][initialcol] = 'b';
                Cboard[moverow][movecol] = ' ';
                Cboard[moverow - 1][movecol] = movespacecolor;
                isvalid = false;
                updateWchecksboard(board, Wchecksboard);
                if (properrun == true) {
                    cout << "cannot make that move as the king will be in check after making the move" << endl;
                }

            }  if (properrun == false) {// if the run is not proper the move is reversed 
                board[initialrow][initialcol] = identifier;
                board[moverow][movecol] = ' ';
                board[moverow - 1][movecol] = movespaceidentifier;
                Cboard[initialrow][initialcol] = 'w';
                Cboard[moverow][movecol] = ' ';
                Cboard[moverow - 1][movecol] = movespacecolor;
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol - 1 == movecol && board[moverow][movecol] == ' ' && board[moverow - 1][movecol] == 'P' && initialrow == 4 && Bpreviousboard[initialrow + 2][initialcol - 1] == 'P' && Bpreviousboard[initialrow][initialcol - 1] == ' ') {//en passant 
            movespaceidentifier = board[moverow - 1][movecol];//special move so will require different reversing methods
            movespacecolor = Cboard[moverow - 1][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            board[moverow - 1][movecol] = ' '; //en passant second side
            Cboard[initialrow][initialcol] = ' ';
            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this do the move on both the chessboard and the color board
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard,properrun);// check if the black king is checked 
            if (ischeck == true) {// if the king is checked then reverse the move and flag the move as invalid
                board[initialrow][initialcol] = identifier;
                board[moverow][movecol] = ' ';
                board[moverow - 1][movecol] = movespaceidentifier;
                Cboard[initialrow][initialcol] = 'b';
                Cboard[moverow][movecol] = ' ';
                Cboard[moverow - 1][movecol] = movespacecolor;
                isvalid = false;
                updateWchecksboard(board, Wchecksboard);
                if (properrun == true) {
                    cout << "cannot make that move as the king will be in heck after making the move" << endl;
                }
            }if (properrun == false) {// if the run is not proper the move is reversed 
                board[initialrow][initialcol] = identifier;
                board[moverow][movecol] = ' ';
                board[moverow - 1][movecol] = movespaceidentifier;
                Cboard[initialrow][initialcol] = 'w';
                Cboard[moverow][movecol] = ' ';
                Cboard[moverow - 1][movecol] = movespacecolor;
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else  if (initialrow + 1 == moverow && initialcol == movecol && board[moverow][movecol] == ' ') {//regular forward movement of pawn
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';

            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';

            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this do the move on both the chessboard and the color board
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard,properrun);// check if the black king is checked 
            if (ischeck) {// if the king is checked then reverse the move and flag the move as invalid
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol,properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }  if (properrun == false) {// if the run is not proper the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if (initialrow + 1 == moverow && initialcol == movecol - 1 && Cboard[moverow][movecol] == 'w') { //capturing opponents piece diagonally
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';

            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';

            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this do the move on both the chessboard and the color board
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard,properrun);// check if the black king is checked 
            if (ischeck) {// if the king is checked then reverse the move and flag the move as invalid
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol,properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }  if (properrun == false) {// if the run is not proper the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }

        }
        else if (initialrow + 1 == moverow && initialcol == movecol + 1 && Cboard[moverow][movecol] == 'w') {// capturing opponents piece diagonally
            movespaceidentifier = board[moverow][movecol];
            movespacecolor = Cboard[moverow][movecol];
            board[initialrow][initialcol] = ' ';
            board[moverow][movecol] = identifier;
            Cboard[initialrow][initialcol] = ' ';

            Cboard[moverow][movecol] = 'b';
            isvalid = true;
            // the lines before this do the move on both the chessboard and the color board
            updateWchecksboard(board, Wchecksboard);
            ischeck = checkforBcheck(board, Wchecksboard,properrun);// check if the black king is checked 
            if (ischeck) {// if the king is checked then reverse the move and flag the move as invalid
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol,properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
                isvalid = false;
            }  if (properrun == false) {// if the run is not proper the move is reversed 
                reverseBmove(board, Cboard, Wchecksboard, identifier, movespaceidentifier, movespacecolor, initialrow, initialcol, moverow, movecol, properrun, Bpreviousboard);
                updateWchecksboard(board, Wchecksboard);
            }
        }
        else if(properrun==true){// if the run is proper and none of the if functions have been satisfied then the move is invalid and ask the user for a different move 
            cout << "the move is invalid" << endl;
            makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
        }
    }


};
int checkWcheckmate(char board[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]) {//checks for checkmate on the white king 
    int initialrow, initialcol, moverow, movecol;

    int counter = 0;
    bool properrun=false;
    bool Wcheck, check;
    bool isvalid;
    char identifier;
    Wcheck = false;
    for (int i = 0;i < BOARD_SIZE;i++) {//the loop checks if the king is under check by checking if it is on a square which is flagged as a check
        for (int j = 0;j < BOARD_SIZE;j++) {
            if (board[i][j] == 'K' && Bchecksboard[i][j] == 'c') {
                Wcheck = true;
            }

        }
    }
    for (int i = 0;i < BOARD_SIZE;i++) {
        for (int j = 0;j < BOARD_SIZE;j++) {//assigns every square as an initial square
            initialrow = i;
            initialcol = j;
            identifier = board[initialrow][initialcol];
            for (int k = 0;k < BOARD_SIZE;k++) {
                for (int f = 0;f < BOARD_SIZE;f++) {//assigns every square as a desitination square for every initial square
                    moverow = k;
                    movecol = f;
                    isvalid = false;
                    //all the rest of the functions will increment a counter when there are valid moves which do not lead to checks 
                    if (initialrow == moverow && initialcol == movecol) { // will continue to the next iteration if the square being passed as destination is the same as the initial square 
                        continue;
                    }
                    else if (identifier == 'P') {
                        whitePawn::validateWpawn(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun,isvalid, Wpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                    else if (identifier == 'K') {
                        whiteKing::validateWking(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun,isvalid, Wpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                    else if (identifier == 'Q') {
                        whiteQueen::validateWQueen(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid, Wpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                    else if (identifier == 'R') {
                        whiteRook::validateWRook(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid, Wpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                    else if (identifier == 'B') {
                        whiteBishop::validateWBishop(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid, Wpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                    else if (identifier == 'N') {
                        whiteKnight::validateWKnight(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid, Wpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                }
            }
        }
    }
  
    if (counter == 0) {// if the counter is 0 meaning there are no valid moves 
        check = checkforWcheck(board, Bchecksboard,properrun);// check if the king is under check 
        if (check == true) {// if the king is under check flag it as checkmate 
            cout << "the game has ended as white you are under checkmate" << endl;
            return 1;
        }
        else if (check == false) {// if the king is not under check then flag it as stalemate 
            cout << "the game has ended in a stalemate" << endl;
            return 2;
        }
    }
    
        return 0;
    
}
int checkBcheckmate(char board[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
    int initialrow, initialcol, moverow, movecol;

    int counter = 0;
    bool properrun = false;
    bool Wcheck, check;
    bool isvalid;
    char identifier;
    Wcheck = false;
    for (int i = 0;i < BOARD_SIZE;i++) {
        for (int j = 0;j < BOARD_SIZE;j++) {//the loop checks if the king is under check by checking if it is on a square which is flagged as a check
            if (board[i][j] == 'k' && Wchecksboard[i][j] == 'c') {
                Wcheck = true;
            }

        }
    }
    for (int i = 0;i < BOARD_SIZE;i++) {
        for (int j = 0;j < BOARD_SIZE;j++) {//assigns every square as an initial square
            initialrow = i;
            initialcol = j;
            identifier = board[initialrow][initialcol];
            for (int k = 0;k < BOARD_SIZE;k++) {
                for (int f = 0;f < BOARD_SIZE;f++) {//assigns every square as a desitination square for every initial square
                    moverow = k;
                    movecol = f;
                    isvalid = false;
                    //all the rest of the if statements will increment a counter when there are valid moves which do not lead to checks 
                    if (initialrow == moverow && initialcol == movecol) {// will continue to the next iteration if the square being passed as destination is the same as the initial square 
                        continue;
                    }else if (identifier == 'p') {
                        blackPawn::validateBpawn(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid,Bpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                    else if (identifier == 'k') {
                        blackKing::validateBking(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid, Bpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                    else if (identifier == 'q') {
                        blackQueen::validateBQueen(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid, Bpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                    else if (identifier == 'r') {
                        blackRook::validateBRook(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid, Bpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                    }
                    else if (identifier == 'b') {
                        blackBishop::validateBBishop(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid, Bpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }
                  
                    }
                    else if (identifier == 'n') {
                        blackKnight::validateBKnight(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, identifier, Wcheck, properrun, isvalid, Bpreviousboard);
                        if (isvalid == true) {
                            counter++;
                        }

                    }
                }
            }
        }
    }
    
    
    if (counter == 0) {// if the counter is 0 meaning there are no valid moves 
        check = checkforBcheck(board, Wchecksboard, properrun);
        if (check == true) {// if the king is under check then flag it as checkmate
            cout << "the game has ended as black you are under checkmate" << endl;
            return 1;
        }
        else if (check == false) {// if the king is not under check then flag it as stalemate 
            cout << "the game has ended in a stalemate" << endl;
            return 2;
        }
    }
   
        return 0;
    
}
void reverseWmove(char board[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char identifier, char movespaceidentifier, char movespacecolor, int& initialrow, int& initialcol, int& moverow, int& movecol,bool properrun, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
   
    // reverses the white move and if the run is proper it prompts the user for a new move as their king is under check 

    board[initialrow][initialcol] = identifier;
    board[moverow][movecol] = movespaceidentifier;
    Cboard[initialrow][initialcol] = 'w';
    Cboard[moverow][movecol] = movespacecolor;
    if (properrun == true) {
        cout << "invalid move as you will be in check after making the move" << endl;
        makemoveWplayer1(board, Bchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Wpreviousboard);

    }
    
}
void reverseBmove(char board[BOARD_SIZE][BOARD_SIZE], char Cboard[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char identifier, char movespaceidentifier, char movespacecolor, int& initialrow, int& initialcol, int& moverow, int& movecol,bool properrun, char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
   
    // reverses the black move and if the run is proper it prompts the user for a new move as their king is under check 

    board[initialrow][initialcol] = identifier;
    board[moverow][movecol] = movespaceidentifier;
    Cboard[initialrow][initialcol] = 'b';
    Cboard[moverow][movecol] = movespacecolor;
    if (properrun == true) {
        cout << "invalid move as you will be in check after making the move" << endl;
        makemoveBplayer2(board, Wchecksboard, Cboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
    }
  

}
void makemoveWplayer1(char chessboard[BOARD_SIZE][BOARD_SIZE], char Bchecksboard[BOARD_SIZE][BOARD_SIZE], char colorboard[BOARD_SIZE][BOARD_SIZE], int& initialrow, int& initialcol, int& moverow, int& movecol, char Wpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
    bool validsquare, Wcheck;
    char movepiece;
    bool properrun = true;
    bool isvalid=true;
    string coordinate;
    Wcheck = checkforWcheck(chessboard, Bchecksboard,properrun);// checks if the white king is under check 
    do {
        // taking input from the user for initial and final position 
        validsquare = true;
        cout << "what is the initial position of your piece player1?" << endl;
        cin >> coordinate;
        mapcoordinates(coordinate, initialrow, initialcol);//maps user input to row and col indexes 
        movepiece = getboardidentifier(chessboard, initialrow, initialcol);//gets the identifier of the piece on the initiial position 
        cout << "where do you wish to move the piece" << endl;
        cin >> coordinate;
        mapcoordinates(coordinate, moverow, movecol);//maps user input to row and col indexes 
        if (initialrow > 7 || initialrow < 0 || initialcol>7 || initialcol < 0 || moverow > 7 || moverow < 0 || movecol>7 || movecol < 0) {// if the square is not on the board then the square is not valid 
            cout << "please enter a valid square on the board" << endl;
            validsquare = false;
        }
        else if (initialrow==moverow && initialcol==movecol) {// doesnt allow users to move to the same position they are on 
            cout << "you cannot move to the same square you are currently on" << endl;
            validsquare = false;
        }
    } while (validsquare == false);// repeats while the square is not valid 
    // the following will call the move functiuons for the corresponding piece on the initial square 
     if (movepiece == 'P') {
        whitePawn::validateWpawn(chessboard, Bchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Wcheck,properrun,isvalid, Wpreviousboard);
    }
    else if (movepiece == 'K') {
        whiteKing::validateWking(chessboard, Bchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Wcheck,properrun,isvalid,  Wpreviousboard);
    }
    else if (movepiece == 'Q') {
        whiteQueen::validateWQueen(chessboard, Bchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Wcheck, properrun, isvalid,  Wpreviousboard);
    }
    else if (movepiece == 'R') {
         whiteRook::validateWRook(chessboard, Bchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Wcheck, properrun, isvalid, Wpreviousboard);
     }
    else if (movepiece == 'B') {
         whiteBishop::validateWBishop(chessboard, Bchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Wcheck, properrun, isvalid, Wpreviousboard);
     }
    else if (movepiece == 'N') {
         whiteKnight::validateWKnight(chessboard, Bchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Wcheck, properrun, isvalid, Wpreviousboard);
     }
    else {// invalid move if the identifier for the movepiece is not one of white pieces 
        cout << "invalid move" << endl;
        makemoveWplayer1(chessboard, Bchecksboard, colorboard, initialrow, initialcol, moverow, movecol, Wpreviousboard);
    }
     Wpawnpromotion(chessboard, Bchecksboard); // checks for the pawn promotion


}
void makemoveBplayer2(char chessboard[BOARD_SIZE][BOARD_SIZE], char Wchecksboard[BOARD_SIZE][BOARD_SIZE], char colorboard[BOARD_SIZE][BOARD_SIZE], int& initialrow, int& initialcol, int& moverow, int& movecol,char Bpreviousboard[BOARD_SIZE][BOARD_SIZE]) {
    bool validsquare,Bcheck;
    char movepiece;
    bool properrun=true;
    bool isvalid = true;
    string coordinate;
    Bcheck = checkforBcheck(chessboard, Wchecksboard, properrun);// checks if the black king is under check 
    do {
        // taking input from the user for initial and final position 
        validsquare = true;
        cout << "what is the initial position of your piece player2?" << endl;
        cin >> coordinate;
        mapcoordinates(coordinate, initialrow, initialcol);//maps user input to row and col indexes 
        movepiece = getboardidentifier(chessboard, initialrow, initialcol);
        cout << "where do you wish to move the piece" << endl;
        cin >> coordinate;
        mapcoordinates(coordinate, moverow, movecol);//maps user input to row and col indexes 
        if (initialrow > 7 || initialrow < 0 || initialcol>7 || initialcol < 0 || moverow > 7 || moverow < 0 || movecol>7 || movecol < 0) {// if the square is not on the board then the square is not valid 
            cout << "please enter a valid square on the board" << endl;
            validsquare = false;
        }
        else if (initialrow == moverow && initialcol == movecol) {// doesnt allow users to move to the same position they are on 
            cout << "you cannot move to the same square you are currently on" << endl;
            validsquare = false;
        }
    } while (validsquare == false);// repeats while the square is not valid 
    // the following will call the move functiuons for the corresponding piece on the initial square 
    if (movepiece == 'p') {
        blackPawn::validateBpawn(chessboard, Wchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece,Bcheck,properrun,isvalid, Bpreviousboard);
    }
    else if (movepiece == 'k') {
        blackKing::validateBking(chessboard, Wchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece,Bcheck,properrun,isvalid, Bpreviousboard);
    }
    else if (movepiece == 'q') {
        blackQueen::validateBQueen(chessboard, Wchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Bcheck, properrun, isvalid, Bpreviousboard);
    }
    else if (movepiece == 'r') {
        blackRook::validateBRook(chessboard, Wchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Bcheck, properrun, isvalid, Bpreviousboard);
    }
    else if (movepiece == 'b') {
        blackBishop::validateBBishop(chessboard, Wchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Bcheck, properrun, isvalid, Bpreviousboard);
    }
    else if (movepiece == 'n') {
        blackKnight::validateBKnight(chessboard, Wchecksboard, colorboard, initialrow, initialcol, moverow, movecol, movepiece, Bcheck, properrun, isvalid, Bpreviousboard);
    }
    else {// invalid move if the identifier for the movepiece is not one of white pieces 
        cout << "invalid move" << endl;
        makemoveBplayer2(chessboard, Wchecksboard, colorboard, initialrow, initialcol, moverow, movecol, Bpreviousboard);
    }
    Bpawnpromotion(chessboard, Wchecksboard); // checks for the pawn promotion

}
int main() {
    

    string name1, name2,HorT;

    // Get player names from user input
    cout << "Enter name for Player 1: ";
    cin >> name1;

    cout << "Enter name for Player 2: ";
    cin >> name2;
    cout << name1 << " please pick heads or tails: ";
    bool isvalid;
    do {
        isvalid = true;
        cin >> HorT;
        if (HorT!= "heads" && HorT!="tails") {
            cout << "please enter a valid choice" << endl;
            isvalid = false;
        }
    } while (isvalid ==  false);
       
   
    // Seed the random number generator
    srand((time(NULL)));

    // Generate a random number (0 or 1) to represent heads or tails
    int result = rand() % 2;
    if (result == 0 && HorT == "heads") {
        cout << "We're going to flip a coin. The result is heads! " << name1 << " is Player 1(white) and " << name2 << " is Player 2(black)." << endl;
    }
    else if (result==1 && HorT=="tails") {
        cout << "We're going to flip a coin. The result is tails! " << name1 << " is Player 1(white) and " << name2 << " is Player 2(black)." << endl;
    }
    else if (result == 1 && HorT == "heads") {
        cout << "We're going to flip a coin. The result is tails! " << name2 << " is Player 1(white) and " << name1 << " is Player 2(black)." << endl;
    }
    else if (result == 0 && HorT == "tails") {
        cout << "We're going to flip a coin. The result is heads! " << name2 << " is Player 1(white) and " << name1 << " is Player 2(black)." << endl;
    }

    
    int backupcount = 1;
    boardbackup* backupptr = new boardbackup[backupcount];
    bool isrepeat=false;//for the repeating positions
    char Wpreviousboard[BOARD_SIZE][BOARD_SIZE], Bpreviousboard[BOARD_SIZE][BOARD_SIZE];
    char colorboard[BOARD_SIZE][BOARD_SIZE];
    char chessboard[BOARD_SIZE][BOARD_SIZE];
    char Wchecksboard[BOARD_SIZE][BOARD_SIZE];
    char Bchecksboard[BOARD_SIZE][BOARD_SIZE];
    char choice1, choice2;
    int movecol, moverow;
    int initialrow, initialcol;
    int wincondition;// in order to find out if it is checkmate or stalemate
    string coordinate;
    initializeChessboard(chessboard);
    initializecolorboard(colorboard);
    storepreviousboard(chessboard, Wpreviousboard);
    storepreviousboard(chessboard, Bpreviousboard);
    do {
        updateWchecksboard(chessboard, Wchecksboard); // i just added this for updates
        updateBchecksboard(chessboard, Bchecksboard); // i just added this for updates
        bool draw;
        displayChessboard(chessboard);  
        
        wincondition=checkWcheckmate(chessboard, Bchecksboard, colorboard,  Wpreviousboard);//checks for checkmate or stalemate 
        if (wincondition == 1 || wincondition ==2) {//breaks the loop if it is checkmate or stalemate 
            break;
        }
        
        if (backupcount == 1) {// puts the first board onto the backup pointer 
            for (int i = 0;i < BOARD_SIZE;i++) {
                for (int j = 0;j < BOARD_SIZE;j++) {
                    backupptr[0].movebackup[i][j] = chessboard[i][j];
                }
            }
        }
        backupptr = boardrepcheck(backupptr, chessboard, backupcount, isrepeat);// checks for 3 time repitition
        if (isrepeat == true) {// breaks loop if position repeated 3 times
            cout << "the game has ended in a draw due to repition" << endl;
            break;
        }
        mainmenu();
        do {//asks for white players input in the beginning 
            cout << "(white)player 1's turn" << endl;
            cin >> choice1;
            if (choice1 != '1' && choice1 != '2' && choice1 != '3') {
                cout << "please enter a valid input" << endl;
            }
        } while (choice1 != '1' && choice1 != '2' && choice1 != '3');

        draw = first1option(choice1);//checks if they want to draw or resign or continue playing 
        if (draw == true) {// breaks loop if the player wants to draw or resign 
            break;
        }
        else {//otherwise when draw is false ask the user for a move and update the cecks board 
            storepreviousboard(chessboard, Bpreviousboard);//stroing newest board for black to utilize
            makemoveWplayer1(chessboard, Bchecksboard, colorboard, initialrow, initialcol, moverow, movecol,Wpreviousboard);
            updateWchecksboard(chessboard, Wchecksboard);
            backupcount++;
          
        }
        backupptr = boardrepcheck(backupptr, chessboard, backupcount, isrepeat);// checks for 3 time repitition
        if (isrepeat == true) {// breaks loop if position repeated 3 times
            cout << "the game has ended in a draw due to repitition" << endl;
            break;
        }
        updateWchecksboard(chessboard, Wchecksboard); // i just added this for updates
        updateBchecksboard(chessboard, Bchecksboard); // i just added this for updates
        displayChessboard(chessboard);
        wincondition=checkBcheckmate(chessboard, Wchecksboard, colorboard, Bpreviousboard);//checks for checkmate or stalemate 
        if (wincondition == 1 || wincondition == 2) {//breaks the loop if it is checkmate or stalemate 
            break;
        }
        mainmenu();

        do {//asks for white players input in the beginning 
            cout << "(black)player 2's turn" << endl;
            cin >> choice2;
            if (choice2 != '1' && choice2 != '2' && choice2 != '3') {
                cout << "please enter a valid input" << endl;
            }
        } while (choice2 != '1' && choice2 != '2' && choice2 != '3');
        draw = first2option(choice2);//checks if they want to draw or resign or continue playing 
        if (draw == true) {// breaks loop if the player wants to draw or resign 
            break;
        }
        else {//otherwise when draw is false ask the user for a move and update the cecks board 
            storepreviousboard(chessboard, Wpreviousboard);//stroing newest board for white to utilize
            makemoveBplayer2(chessboard, Wchecksboard, colorboard, initialrow, initialcol, moverow, movecol,Bpreviousboard);
            updateBchecksboard(chessboard, Bchecksboard);
            backupcount++;
            
        }
        


    } while (choice1 != 10 && choice2 != 10);// values do not matter as the loop needs to repeat forever unless broken intentionally 

    delete[] backupptr;//deallocates the memory for the pointer 

    return 0;
}



