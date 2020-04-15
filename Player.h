/*
 * Player.h
 *
 *  Created on: Mar 10, 2020
 *      Author: Minh Tran
 */

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
private:
	int color;
public:
	void setColor(int c);
	int getColor();
};

void Player::setColor(int c) {
	color = c;
}

int Player::getColor() {
	return color;
}

class Random_Player : public Player {
private:
	int x;
	int y;
public:
	// void setColor(int color);
	void getRandomX();
	void getRandomY();
};




#endif /* PLAYER_H_ */
