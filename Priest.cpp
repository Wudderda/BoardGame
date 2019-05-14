#include"Priest.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

/**
  * Attack damage 0
  * Heal power 50
  * Max HP 150
  * Goal Priorities -> {HEAL,TO_ALLY,CHEST} in decreasing order
  * Class abbreviation -> "pr" or "PR"
  * Can move to all adjacent squares, including diagonals.
  * Can heal all adjacent squares, including diagonals.
  *
  */
int Priest::getAttackDamage() const{
	return 0;
}
int Priest::getHealPower() const {
	return 50;
}
int Priest::getMaxHP() const {
	return 150;
}
std::vector<Goal> Priest::getGoalPriorityList() {
	std::vector<Goal> a = { HEAL,TO_ALLY,CHEST };
	return a;
}
const std::string Priest::getClassAbbreviation() const {
	if (getTeam() == BARBARIANS) {
		return "PR";
	}
	else {
		return "pr";
	}
}
std::vector<Coordinate> Priest::getAttackableCoordinates() {
	std::vector<Coordinate> a = {};
	return a;
}
std::vector<Coordinate> Priest::getMoveableCoordinates() {
	Coordinate up = getCoord() + Coordinate(0, -1);
	Coordinate down = getCoord() + Coordinate(0, 1);
	Coordinate right = getCoord() + Coordinate(1, 0);
	Coordinate left = getCoord() + Coordinate(-1, 0);
	Coordinate diagnol1 = getCoord() + Coordinate(-1, 1);
	Coordinate diagnol2 = getCoord() + Coordinate(1, -1);
	Coordinate diagnol3 = getCoord() + Coordinate(1, 1);
	Coordinate diagnol4 = getCoord() + Coordinate(-1, -1);
	std::vector<Coordinate> a = { right,left,up,down,diagnol4,diagnol2,diagnol3,diagnol1};
	return a;
}
std::vector<Coordinate> Priest::getHealableCoordinates() {
	Coordinate up = getCoord() + Coordinate(0, -1);
	Coordinate down = getCoord() + Coordinate(0, 1);
	Coordinate right = getCoord() + Coordinate(1, 0);
	Coordinate left = getCoord() + Coordinate(-1, 0);
	Coordinate diagnol1 = getCoord() + Coordinate(-1, -1);
	Coordinate diagnol2 = getCoord() + Coordinate(1, 1);
	Coordinate diagnol3 = getCoord() + Coordinate(1, -1);
	Coordinate diagnol4 = getCoord() + Coordinate(-1, 1);
	std::vector<Coordinate> a = { up,down,right,left,diagnol4,diagnol2,diagnol3,diagnol1 };
	return a;
}