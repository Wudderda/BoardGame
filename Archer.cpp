#include"Archer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
/**
  * Attack damage 50
  * Heal power 0
  * Max HP 200
  * Goal Priorities -> {ATTACK}
  * Class abbreviation -> "ar" or "AR"
  * Not able to move at all.
  * Can attack to a range of 2 squares directly up, down, left or right, from
  * its coordinate.
  *
  */
int Archer::getAttackDamage() const {
	return 50;
	 }
int Archer::getHealPower() const {
	return 0;
	 }
int Archer::getMaxHP() const {
	return 200;
	 }
std::vector<Goal> Archer::getGoalPriorityList() {
	std::vector<Goal> a = { ATTACK };
	return a;
}
const std::string Archer::getClassAbbreviation() const {
	if (getTeam() == BARBARIANS) {
		return "AR";
	}
	else {
		return "ar";
	}
	 }
std::vector<Coordinate> Archer::getAttackableCoordinates() {
	Coordinate up2 = getCoord() + Coordinate(1, 0);
	Coordinate down2 = getCoord() + Coordinate(-1, 0);
	Coordinate right2 = getCoord() + Coordinate(0, 1);
	Coordinate left2 = getCoord() + Coordinate(0, -1);
	Coordinate up = getCoord() + Coordinate(0, -2);
	Coordinate down = getCoord() + Coordinate(0, 2);
	Coordinate right = getCoord() + Coordinate(2, 0);
	Coordinate left = getCoord() + Coordinate(-2, 0);
	std::vector<Coordinate> a = { up2,down2,right2,left2,up,down,right,left };
	return a;
	 }
	 std::vector<Coordinate> Archer::getMoveableCoordinates() {
		 std::vector<Coordinate> a = {};
		 return a;
	 }
	 std::vector<Coordinate> Archer::getHealableCoordinates() {
		 std::vector<Coordinate> a = {};
		 return a;
	 }