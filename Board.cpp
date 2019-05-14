#include"Board.h"
#include<vector>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
bool Board::isCoordinateInBoard(const Coordinate& c) {
	if (c.x <size && c.x >0 && c.y <size && c.y >0) {
		return true;
	}
	else {
		return false;
	}
}
/**
 * @return true if there is a player on the given coordinate, false otherwise.
 */
bool Board::isPlayerOnCoordinate(const Coordinate& c) {
	for (int i = 0; i < players->size(); i++) {
		if ((*players)[i]->getCoord() == c) {
			return true;
		}
	}
	return false;
}
/**
 * @return pointer to the player at the given coordinate. Return NULL if no
 * player is there.
 */
Player* Board::operator [](const Coordinate& c) {
	for (int i = 0; i < players->size(); i++) {
		if ((*players)[i]->getCoord() == c) {
			return (*players)[i];
		}
	}
	return NULL;
}

/**
 * @return the chest coordinate
 */
Coordinate Board::getChestCoordinates() {
	return chest;
}
/**
 * Print the board with character ID's.
 * For each empty square print two underscore characters.
   * For the squares with a player on it, print the board id of the player.
   * For the square with the chest, print the string "Ch".
   * If a character is on the square with the chest, only print the ID of the
   * character.
   * For each row print a new line, for each column print a space character.
   * Example:
   * __ __ 01 __
   * __ 02 __ 05
   *	Ch __ __ 03
   *	__ __ __ __
 */
void Board::printBoardwithID() {
	int flag = 0;
	if (isPlayerOnCoordinate(chest) != NULL) {
		flag = 1;
	}
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			if (i != 0) {
				std::cout << " ";
			}
			if (Coordinate(i, j) == chest) {
				if (flag == 1) {
					std::cout << (*this)[Coordinate(i, j)]->getBoardID();
				}
				else {
					std::cout << "Ch";
				}
			}
			else if (isPlayerOnCoordinate(Coordinate(i, j)) == NULL) {
				std::cout << "__";
			}
			else {
					std::cout << (*this)[Coordinate(i, j)]->getBoardID();
			}
		}
		std::cout << std::endl;
	}

}
/**
 * For each empty square print two underscore characters.
 * For the squares with a player on it, print the class abbreviation of the
 * player.
 * For the square with the chest, print the string "Ch".
 * If a character is on the square with the chest, only print the abbreviation
 * of the character.
 * To separate each row print a new line, to separate each column print a
 * space character.
 * Example:
 * __ __ PR __
 * __ ar __ TA
 * Ch __ __ fi
 * __ __ __ __
 */
void Board::printBoardwithClass() {
	int flag = 0;
	if (isPlayerOnCoordinate(chest) != NULL) {
		flag = 1;
	}
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			if (i != 0) {
				std::cout <<" ";
			}
			if (Coordinate(i,j) == chest) {
				if (flag == 1) {
					std::cout << (*this)[Coordinate(i, j)]->getClassAbbreviation();
				}
				else {
					std::cout << "Ch";
				}
			}
			else if (isPlayerOnCoordinate(Coordinate(i, j)) == NULL) {
				std::cout << "__";
			}
			else {
					std::cout << (*this)[Coordinate(i, j)]->getClassAbbreviation();
			}
		}
		std::cout << std::endl;
	}
}