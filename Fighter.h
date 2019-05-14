#ifndef HW4_FIGHTER_H
#define HW4_FIGHTER_H

#include"Player.h"

class Fighter : public Player{
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
public:
	Fighter(unsigned int id, int x, int y, Team team) :Player(id, x, y, team,400){};
	virtual ~Fighter() = default;
	virtual int getAttackDamage() const;
	virtual int getHealPower() const;
	virtual int getMaxHP() const;
	virtual std::vector<Goal> getGoalPriorityList();
	virtual const std::string getClassAbbreviation() const;
	virtual std::vector<Coordinate> getAttackableCoordinates();
	virtual std::vector<Coordinate> getMoveableCoordinates();
	virtual std::vector<Coordinate> getHealableCoordinates();
};

#endif
