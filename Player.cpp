#include"Player.h"
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

	unsigned int Player::getID() const{
		return id;
	}
	const Coordinate& Player::getCoord() const{
		return coordinate;
	}

	int Player::getHP() const{
		return HP;
	}

	Team Player::getTeam() const{
		return team;
	}
	std::string Player::getBoardID(){
		if (id >= 0 && id <= 9) {
			std::string a;
			char b = '0' + id;
			a = { '0',b };
			return a;
		}
		else {
			std::string c;
			char a = id / 10 + '0';
			char b = id % 10 + '0';
			c = { a,b};
			return c;
		}
	}
	bool Player::attack(Player *enemy){
		std::cout << "Player " << getBoardID() << " attacked Player " << enemy->getBoardID() << " (" << getAttackDamage() << ")"<<std::endl;
		enemy->addHP(-getAttackDamage());
		if(enemy->isDead()){
			return true;
		}
		else{ return false;}
	}
	void Player::heal(Player *ally){
		std::cout << "Player " << getBoardID() << " healed " << "Player " << ally->getBoardID()<<std::endl;
		ally->addHP(getHealPower());
	}
	void Player::addHP(int a){
		if(HP+a>getMaxHP()){
			HP=getMaxHP();
		}
		else if (HP + a < 0) {
			HP = 0;
		}
		else{
			HP+=a;
		}
	}
	void Player::movePlayerToCoordinate(Coordinate c){
		std::cout<<"Player "<<getBoardID()<<" moved from ("<<getCoord().x<<"/"<<getCoord().y;
		coordinate=c;
		std::cout << ") to (" << getCoord().x << "/" << getCoord().y << ")"<<std::endl;
	}
	bool Player::isDead() const{
		if (getHP() <= 0) {
			return true;
		}
		else {
			return false;
		}
	}