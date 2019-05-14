#include"Scout.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

/**
 * Attack damage 25
 * Heal power 0
 * Max HP 125
 * Goal Priorities -> {CHEST,TO_ALLY,ATTACK} in decreasing order
 * Class abbreviation -> "sc" or "SC"
 * Can move to all adjacent squares, including diagonals.
 * Can attack all adjacent squares, including diagonals.
 *
 */
int Scout::getAttackDamage() const {
	return 25;
	 }
int Scout::getHealPower() const {
	return 0;
	 }
int Scout::getMaxHP() const {
	return 125;
	 }
std::vector<Goal> Scout::getGoalPriorityList() {
	std::vector<Goal> a = { CHEST,TO_ALLY,ATTACK };
	return a;
	 }
const std::string Scout::getClassAbbreviation() const {
	if (getTeam() == BARBARIANS) {
		return "SC";
	}
	else {
		return "sc";
	}
	 }
std::vector<Coordinate> Scout::getAttackableCoordinates() {
	Coordinate up = getCoord() + Coordinate(0, -1);
	Coordinate down = getCoord() + Coordinate(0, 1);
	Coordinate right = getCoord() + Coordinate(1, 0);
	Coordinate left = getCoord() + Coordinate(-1, 0);
	Coordinate diagnol1 = getCoord() + Coordinate(-1, -1); // sol aþþaðý
	Coordinate diagnol2 = getCoord() + Coordinate(1, 1); //sað yukarý
	Coordinate diagnol3 = getCoord() + Coordinate(1, -1);//sað aþþaðý
	Coordinate diagnol4 = getCoord() + Coordinate(-1, 1);// sol yukarý
	std::vector<Coordinate> a = { up,down,right,left,diagnol4,diagnol2,diagnol3,diagnol1 };
	return a;
	 }
std::vector<Coordinate> Scout::getMoveableCoordinates() {
	Coordinate up = getCoord() + Coordinate(0, -1);
	Coordinate down = getCoord() + Coordinate(0, 1);
	Coordinate right = getCoord() + Coordinate(1, 0);
	Coordinate left = getCoord() + Coordinate(-1, 0);
	Coordinate diagnol1 = getCoord() + Coordinate(-1, 1);
	Coordinate diagnol2 = getCoord() + Coordinate(1, -1);
	Coordinate diagnol3 = getCoord() + Coordinate(1, 1);
	Coordinate diagnol4 = getCoord() + Coordinate(-1, -1);
	std::vector<Coordinate> a = { right,left,up,down,diagnol4,diagnol2,diagnol3,diagnol1 };
	return a;
}
	 std::vector<Coordinate>Scout::getHealableCoordinates() {
		 std::vector<Coordinate> a = {};
		 return a;
	 }
