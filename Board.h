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

const int EMPTY_NODE = 0;
const int BLUE = 1;
const int RED = -1;

class Board {
private:
	int **board;
	int moveNum;
	int boardSize;
public:
	Board();
	void setBoardSize(int board_size);
	bool isBoardFull();
	int getWinner();
	bool BFS(int player, int x, int y);
	vector<pair<int, int>> adjacentNodes(int player, bool **visited, int x, int y);
	bool isValidIndex(int index);
	bool isValidMove(int player, int x, int y);
	bool addPlayerMove(int player, int x, int y);
	void printBoard();
	void setBoard() {
		int grid[4][4] = { { -1, 0, 0, 0 }, { -1, 0, -1, -1 }, { -1, 1, 0, -1 },
				{ -1, 1, 0, -1 } };
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				board[i][j] = grid[i][j];
			}
		}

	}
	;
	~Board();
};

Board::Board() {
	boardSize = 0;
	moveNum = 0;
	board = 0;
}

void Board::setBoardSize(int board_size) {
	boardSize = board_size;
	board = new int *[boardSize];

	for (int i = 0; i < boardSize; i++) {
		board[i] = new int[boardSize];
	}

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = EMPTY_NODE;
		}
	}
}

bool Board::BFS(int player, int x, int y) {
	pair<int, int> temp;
	vector<pair<int, int>> adjacentNodesVect;
	bool **visited;
	visited = new bool *[boardSize];

	// Initialize visited
	for (int i = 0; i < boardSize; i++) {
		visited[i] = new bool[boardSize];
	}

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			visited[i][j] = false;
		}
	}

	// List for adjacent nodes
	list<pair<int, int>> adjacentList;

	// Mark fist node as visited and add it to the list
	visited[x][y] = true;
	adjacentList.push_back(make_pair(x, y));

	while (!adjacentList.empty()) {
		// Remove front element of the list
		temp = adjacentList.front();
		adjacentList.pop_front();

		// END condition
		if (player == RED && temp.first == boardSize - 1) {
			return true;
		} else if (player == BLUE && temp.second == boardSize - 1) {
			return true;
		}

		// Find adjacent nodes and add them to list
		if (player == RED) {
			adjacentNodesVect = adjacentNodes(RED, visited, temp.first, temp.second);
		} else {
			adjacentNodesVect = adjacentNodes(BLUE, visited, temp.first, temp.second);
		}
		for (auto it : adjacentNodesVect) {
			if (!visited[it.first][it.second]) {
				visited[it.first][it.second] = true;
				adjacentList.push_back(make_pair(it.first, it.second));
			}
		}

	}
	return false;
}

vector<pair<int, int>> Board::adjacentNodes(int player, bool **visited, int x, int y) {
	vector<pair<int, int>> myVect;

	// TOP LEFT NODE
	if (y - 1 > 0 && x - 1 > 0 && visited[x - 1][y - 1] == false
			&& board[x - 1][y - 1] == player) {
		myVect.push_back(make_pair(x - 1, y - 1));
	}

	// TOP NODE
	if (x - 1 > 0 && visited[x - 1][y] == false && board[x - 1][y] == player) {
		myVect.push_back(make_pair(x - 1, y));
	}

	// TOP RIGHT NODE
	if (y + 1 < boardSize && x - 1 > 0 && visited[x - 1][y + 1] == false
			&& board[x - 1][y + 1] == player) {
		myVect.push_back(make_pair(x - 1, y + 1));
	}

	// LEFT NODE
	if (y - 1 > 0 && visited[x][y - 1] == false && board[x][y - 1] == player) {
		myVect.push_back(make_pair(x, y - 1));
	}

	// RIGHT NODE
	if (y + 1 < boardSize && visited[x][y + 1] == false
			&& board[x][y + 1] == player) {
		myVect.push_back(make_pair(x, y + 1));
	}

	// LEFT BOTTOM
	if (x + 1 < boardSize && y - 1 > 0 && visited[x + 1][y - 1] == false
			&& board[x + 1][y - 1] == player) {
		myVect.push_back(make_pair(x + 1, y - 1));
	}

	// MID BOTTOM
	if (x + 1 < boardSize && visited[x + 1][y] == false
			&& board[x + 1][y] == player) {
		myVect.push_back(make_pair(x + 1, y));
	}

	// RIGHT BOTTOM
	if (x + 1 < boardSize && y + 1 < 4 && visited[x + 1][y + 1] == false
			&& board[x + 1][y + 1] == player) {
		myVect.push_back(make_pair(x + 1, y + 1));
	}

	return myVect;
}

int Board::getWinner() {
	for (int i = 0; i < boardSize; ++i) {
		if (board[0][i] == RED) {
			if (BFS(RED, 0, i)) {
				return RED;
			}
		}
	}

	for (int i = 0; i < boardSize; ++i) {
		if (board[i][0] == BLUE) {
			if (BFS(BLUE, i, 0)) {
				return BLUE;
			}
		}
	}
	return 0;
}

bool Board::isBoardFull() {
	return moveNum == boardSize * boardSize;
}

bool Board::isValidIndex(int index) {
	return index >= 0 && index < boardSize;
}

bool Board::isValidMove(int player, int x, int y) {
	return !isBoardFull() && isValidIndex(x) && isValidIndex(y)
			&& board[x][y] == 0;
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

void Board::printBoard() {
	int numChar = 1;
	cout << "---------------------------------------\nBoard status:\n\n";
	string x_axis = "    ";
	for (int i = 0; i < boardSize; i++) {
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
	for (int i = 0; i < boardSize; i++) {
		cout << i + 1 << " | ";
		for (int j = 0; j < boardSize; j++) {
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
	cout << "\n---------------------------------------\n";
}

Board::~Board() {
	for (int i = 0; i < boardSize; i++) {
		delete[] board[i];
	}
	delete[] board;
}

/*
 void countBoard() {
 int b, r;
 b = 0;
 r = 0;
 for (int i = 0;i < boardSize; i++) {
 for (int j = 0; j < boardSize; j++) {
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
