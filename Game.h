/*
 * Game.h
 *
 *  Created on: Mar 10, 2020
 *      Author: Minh Tran
 */

#ifndef GAME_H_
#define GAME_H_

#include<iostream>
#include<vector>
#include<list>
#include<math.h>
#include"Player.h"
#include"Board.h"

using namespace std;

const int NUMBER_OF_PLAYERS = 2;
const char HUMAN_PLAYER = 'H';
const char RANDOM_PLAYER = 'R';
const char AI_PLAYER = 'A';

class Game {
private:
	vector<char> players;
	Board board;
	int boardSize;
public:
	Game();
	int getBoardSize();
	void getPlayers();
	void getCoordinateHuman();
	void getCoordinateRandom();
	bool isBoardFull();
	bool isValidBoardSize(int boardSize);
	void run();
};

Game::Game() {
	boardSize = getBoardSize();
	board.setBoardSize(boardSize);
	players.reserve(NUMBER_OF_PLAYERS);
}

bool Game::isValidBoardSize(int boardSize) {
	return boardSize >= 3 && boardSize <= 15;
}

bool Game::isBoardFull() {
	return board.isBoardFull();
}

int Game::getBoardSize() {
	int board_size = 0;
	while (!isValidBoardSize(board_size)) {
		cout << "Enter board size: \n";
		cin >> board_size;
		if (!isValidBoardSize(board_size))
			cout
					<< "Invalid board size, board size can only be between 3 and 15 inclusive.\n";
	}
	return board_size;
}

// Assuming you are always red by default.
void Game::getPlayers() {
	int choices = 0;
	players.push_back(HUMAN_PLAYER);

	while (choices < 1 || choices > 3) {
		cout << "Choose your opponent: \n" << "1. Human player\n"
				<< "2. Random player\n" << "3. AI player\n";
		cin >> choices;
		switch (choices) {
		case 1:
			Player human;
			human.setColor(BLUE);
			players.push_back(HUMAN_PLAYER);
			break;
		case 2:
			Random_Player random_player;
			random_player.setColor(BLUE);
			players.push_back(RANDOM_PLAYER);
			break;
		case 3:
			// AI player
			players.push_back(AI_PLAYER);
			break;
		default:
			cout << "Invalid choice, please enter 1,2 or 3.\n";
			break;
		}
	}
}

void Game::getCoordinateHuman() {
	vector<int> coordinate;
	int currentPlayer = RED;
	int x = 0;
	int y = 0;
	int winnerInt = 0;
	bool ended = false;

	while (!ended) {
		if (currentPlayer == RED) {
			cout << "Player Red, Enter X and Y coordinate respectively: \n";
			cin >> x >> y;
			if (board.addPlayerMove(currentPlayer, x, y)) {
				currentPlayer = BLUE;
			} else {
				cout << "Invalid move\n";
			}
		} else {
			cout << "Player Blue, Enter X and Y coordinate respectively: \n";
			cin >> x >> y;
			if (board.addPlayerMove(currentPlayer, x, y)) {
				currentPlayer = RED;
			} else {
				cout << "Invalid move\n";
			}
		}
		board.printBoard();
		coordinate.push_back(x);
		coordinate.push_back(y);
		winnerInt = board.getWinner();
		if (winnerInt != 0) {
			if (winnerInt == RED) {
				cout << "RED player has won. GAME OVER!!!";
			} else {
				cout << "BLUE player has won. GAME OVER!!!";
			}
			cout << "\n---------------------------------------\n";
			ended = true;
		}
	}
}

void Game::getCoordinateRandom() {
	vector<int> coordinate;
	int currentPlayer = RED;
	int x = 0;
	int y = 0;
	int winnerInt = 0;
	bool ended = false;
	bool added = false;
	srand(time(NULL));

	while (!ended) {
		if (currentPlayer == RED) {
			cout << "Player Red, Enter X and Y coordinate respectively: \n";
			cin >> x >> y;
			if (board.addPlayerMove(currentPlayer, x, y)) {
				currentPlayer = BLUE;
			} else {
				cout << "Invalid move\n";
			}
		} else {
			x = rand() % boardSize + 1;
			y = rand() % boardSize + 1;
			printf("Random move (%d, %d)\n", x, y);
			added = board.addPlayerMove(currentPlayer, x, y);
			if (added) {
				currentPlayer = RED;
			}
		}
		board.printBoard();
		coordinate.push_back(x);
		coordinate.push_back(y);
		winnerInt = board.getWinner();
		if (winnerInt != 0) {
			if (winnerInt == RED) {
				cout << "RED player has won. GAME OVER!!!";
			} else {
				cout << "BLUE player has won. GAME OVER!!!";
			}
			cout << "\n---------------------------------------\n";
			ended = true;
		}
	}
}

void Game::run() {
	board.printBoard();
	getPlayers();
	switch (players[1]) {
	case HUMAN_PLAYER:
		getCoordinateHuman();
		break;
	case RANDOM_PLAYER:
		getCoordinateRandom();
		break;
	case AI_PLAYER:
		break;
	}
}

#endif /* GAME_H_ */
