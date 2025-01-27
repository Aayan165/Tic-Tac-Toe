#include<iostream>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

using namespace std;

//Global Variables
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

//Function Prototype
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main() {
	char winner = ' ';

	resetBoard();

	while(winner == ' ' && checkFreeSpaces() != 0) {
		printBoard();

		playerMove();
		winner = checkWinner();
		if(winner != ' ' || checkFreeSpaces() == 0){
			break;
		}
		
		computerMove();
		winner = checkWinner();
		if(winner != ' ' || checkFreeSpaces() == 0){
			break;
		}
	}
	printBoard();
	printWinner(winner);


	return 0;
}

//Function Definition
void resetBoard() {
	for(int i=0; i<3; i++) {
		for(int j=0 ; j<3 ; j++) {
			board[i][j] = ' ';
		}
	}
}

void printBoard() {
	for(int i=0; i<3; i++) {
		for(int j=0 ; j<3 ; j++) {
			cout<<" "<<board[i][j]<<" ";
			if(j<2) {
				cout<<"|";
			}
		}
		if(i<2) {
			cout<<"\n---|---|---";
		}
		cout<<"\n";
	}
}

int checkFreeSpaces() {
	int freeSpaces = 9;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			if(board[i][j] != ' ') {
				freeSpaces--;
			}
		}
	}
	return freeSpaces;
}

void playerMove() {
	int x, y;

	do {
		printf("Enter row number (1-3): ");
		cin>>y;
		y--;
		printf("Enter coloumn number (1-3): ");
		cin>>x;
		x--;

		if(board[y][x] != ' ') {
			cout<<"\nInvalid Move\n";
		} else {
			board[y][x] = PLAYER;
			break;
		}
	}while(board[y][x] != ' ');

}

void computerMove(){

	//Check if computer is winning on next move
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == ' '){
                board[i][j] = COMPUTER;
                if(checkWinner() == COMPUTER){
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

	//Check if player is winning on next move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = PLAYER;
                if (checkWinner() == PLAYER) {
                    board[i][j] = COMPUTER;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    //If noone is winning on next move
    srand(time(0));
    int x, y;
    if (checkFreeSpaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    } else {
        printWinner(' ');
    }
}

char checkWinner() {
	
	//Check rows
	for(int i=0 ; i<3 ; i++){
		if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
			return board[i][0];
		}
	}
	
	//Check coloumns
	for(int i=0 ; i<3 ; i++){
		if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
			return board[0][i];
		}
	}
	
	//Check diagonals
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
		return board[0][0];
	}
	if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
		return board[0][2];
	}
	return ' ';
}

void printWinner(char winner) {
	if(winner == PLAYER){
		cout<<"You Win!";
	}
	else if(winner == COMPUTER){
		cout<<"You Lose!";
	}
	else{
		cout<<"It's a Tie!";
	}
}