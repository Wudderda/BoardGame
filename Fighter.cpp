#include"Fighter.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

/**
   * Attack damage 100
   * Heal power 0
   * Max HP 400
   * Goal Priorities -> {ATTACK,TO_ENEMY,CHEST} in decreasing order
   * Class abbreviation -> "fi" or "FI"
   * Can move to adjacent up, down, left or right square
   * Can attack to adjacent up, down, left or right square
   *
   */
int Fighter::getAttackDamage() const {
	return 100;
}

int Fighter::getHealPower() const {
	return 0;
}

int Fighter::getMaxHP() const {
	return 400;
}
/**
	 * For each subclass of Player there are different priority lists defined
	 * that controls the next action to take for that Player. It is given in the
	 * header of the subclasses.
	 *
	 * @return the goal priority list for the Player
	 */
std::vector<Goal> Fighter::getGoalPriorityList() {
	std::vector<Goal> a = { ATTACK,TO_ENEMY,CHEST };
	return a;
}
/**
	 * @return the class abbreviation of player, if the player is on the barbarian
	 * team, the abbreviation will consist of uppercase characters, otherwise it
	 * will consist of lowercase characters.
	 *
	 */
const std::string Fighter::getClassAbbreviation() const {
	if (getTeam() == BARBARIANS) {
		return "FI";
	}
	else {
		return "fi";
	}
}
/**
	 * @Important The coordinates may not be on the board.
	 *
	 * @return the coordinates that the unit is able to attack given the position
	 * of the unit. Empty vector if the unit cannot attack.
	 */

std::vector<Coordinate> Fighter::getAttackableCoordinates() {
	Coordinate up = getCoord() + Coordinate(1, 0);
	Coordinate down = getCoord() + Coordinate(-1, 0);
	Coordinate right = getCoord() + Coordinate(0, 1);
	Coordinate left = getCoord() + Coordinate(0, -1);
	std::vector<Coordinate> a = { up,down,right,left };
	return a;
}
/**
	 * @Important The coordinates may not be on the board.
	 *
	 * @return the coordinates the unit is able to move given the position of the
	 * unit. Empty vector if the unit cannot move.
	 */
std::vector<Coordinate> Fighter::getMoveableCoordinates() {
	Coordinate up = getCoord() + Coordinate(0, -1);
	Coordinate down = getCoord() + Coordinate(0, 1);
	Coordinate right = getCoord() + Coordinate(1, 0);
	Coordinate left = getCoord() + Coordinate(-1, 0);
	std::vector<Coordinate> a = { right,left,up,down };
	return a;
}
/**
	 *
	 * @return the coordinates the unit is able to heal allies given the position of the
	 * unit. Empty vector if none available.
	 */
std::vector<Coordinate> Fighter::getHealableCoordinates() {
	std::vector<Coordinate> a = {};
	return a;
}
