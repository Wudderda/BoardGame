#include"Tank.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
/**
  * Attack damage 25
  * Heal power 0
  * Max HP 1000
  * Goal Priorities -> {TO_ENEMY,ATTACK,CHEST} in decreasing order
  * Class abbreviation -> "ta" or "TA"
  * Can move to adjacent up, down, left or right square
  * Can attack to adjacent up, down, left or right square
  *
  */
int Tank::getAttackDamage() const {
	return 25;
	 }
int Tank::getHealPower() const {
	return 0;
	 }
int Tank::getMaxHP() const {
	return 1000;
	 }
std::vector<Goal> Tank::getGoalPriorityList() {
	std::vector<Goal> a = { TO_ENEMY,ATTACK,CHEST };
	return a;
	 }
const std::string Tank::getClassAbbreviation() const {
	if (getTeam() == BARBARIANS) {
		return "TA";
	}
	else {
		return "ta";
	}
	 }
std::vector<Coordinate> Tank::getAttackableCoordinates() {
	Coordinate up = getCoord() + Coordinate(0, -1);
	Coordinate down = getCoord() + Coordinate(0, 1);
	Coordinate right = getCoord() + Coordinate(1, 0);
	Coordinate left = getCoord() + Coordinate(-1, 0);
	std::vector<Coordinate> a = { up,down,right,left };
	return a;
	 }
std::vector<Coordinate>Tank::getMoveableCoordinates() {
	Coordinate up = getCoord() + Coordinate(0, -1);
	Coordinate down = getCoord() + Coordinate(0, 1);
	Coordinate right = getCoord() + Coordinate(1, 0);
	Coordinate left = getCoord() + Coordinate(-1, 0);
	std::vector<Coordinate> a = { right,left,up,down };
	return a;
}
	 std::vector<Coordinate> Tank::getHealableCoordinates() {
		 std::vector<Coordinate> a = {};
		 return a;
	 }