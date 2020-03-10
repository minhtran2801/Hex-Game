#include <iostream>
#include "Board.h"
using namespace std;

int main() {
	Board b;
	b.generateRandom();
	b.printBoard();
	return 0;
}
