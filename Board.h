/*
 * Board.h
 *
 *  Created on: Mar 9, 2020
 *      Author: Minh Tran
 */

#ifndef BOARD_H_
#define BOARD_H_

#include<iostream>
#include<iomanip>
#include<string>
#include<stdlib.h>

using namespace std;

const int BOARD_SIZE = 8;
const int EMPTY_NODE = 0;
const int BLUE = 1;
const int RED = -1;

class Board {
private:
	int **board;
	int moveNum;
public:
	Board();
	bool isBoardFull();
	bool isValidIndex(int index);
	bool isValidMove(int player, int x, int y);
	bool addPlayerMove(int player, int x, int y);
	void generateRandom();
	void printBoard();
	~Board();
};

Board::Board() {
	board = new int *[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++) {
		board[i] = new int[BOARD_SIZE];
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = EMPTY_NODE;
		}
	}

	moveNum = 0;
}

bool Board::isBoardFull() {
	return moveNum == BOARD_SIZE * BOARD_SIZE;
}

bool Board::isValidIndex(int index) {
	return index >= 0 && index < BOARD_SIZE;
}

bool Board::isValidMove(int player, int x, int y) {
	return (board[x][y] == 0) && !isBoardFull() && isValidIndex(x)
			&& isValidIndex(y);
}

bool Board::addPlayerMove(int player, int x, int y) {
	int x_index = x - 1;
	int y_index = y - 1;
	if (isValidMove(player, x_index, y_index)) {
		board[x_index][y_index] = player;
		moveNum++;
		return true;
	}
	return false;
}

void Board::generateRandom() {
	int player, randomX, randomY;
	bool isAdded = false;
	randomX = -1;
	randomY = -1;
	player = BLUE;
	srand(time(NULL));
	while (!isBoardFull()) {
		randomX = rand() %  BOARD_SIZE + 1;
		randomY = rand() % BOARD_SIZE + 1;

		isAdded = addPlayerMove(player, randomX, randomY);
		if (isAdded && player == BLUE) {
			player = RED;
		} else if (isAdded && player == RED) {
			player = BLUE;
		}
	}
}

void Board::printBoard() {
	int numChar = 1;
	string x_axis = "    ";
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (i == 0) {
			x_axis += to_string(i + 1);
		} else {
			x_axis += "   " + to_string(i + 1);
		}

	}
	cout << x_axis << endl;
	cout << "  ";
	for (int i = 0; i < x_axis.length() - 1; i++) {
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << i + 1 << " | ";
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == RED) {
				cout << "R" << " | ";
			} else if (board[i][j] == BLUE) {
				cout << "B" << " | ";
			} else {
				cout << "  | ";
			}
		}
		numChar += 2;
		cout << endl << setw(numChar);
	}
	cout << setw(numChar);
	for (int i = 0; i < x_axis.length(); i++) {
		cout << "-";
	}
}

Board::~Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		delete[] board[i];
	}
	delete[] board;
}
/*
void countBoard() {
		int b, r;
		b = 0;
		r = 0;
		for (int i = 0;i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (board[i][j] == BLUE) {
					b++;
				} else if (board[i][j] == RED) {
					r++;
				}

			}
		}
		cout << b << " " << r << endl;
	}
*/
#endif /* BOARD_H_ */
