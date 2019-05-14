#include"Game.h"
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Game::Game(unsigned int max, unsigned int boardSize, Coordinate chest): board(Board(boardSize, &players, chest)) {
	maxTurnNumber = max;
	turnNumber = 0;
}
/**
   * Add a new player to the game. Add a pointer to the new player to the this->players vector.
   * Do not forget that Game will manage the memory allocated for the players.
   * @param id ID of the new player.
   * @param x x coordinate of the new player.
   * @param y y coordinate of the new player.
   * @param team team of the new player.
   * @param cls class of the new player as string, One of "ARCHER", "FIGHTER",
   * "PRIEST", "SCOUT", "TANK".
   *
   */
void Game::addPlayer(int id, int x, int y, Team team, std::string cls) {
	Player* player;
	if (cls == "ARCHER") {
		player = new Archer(id, x, y, team);
	}
	else if (cls == "FIGHTER") {
		player = new Fighter(id, x, y, team);
	}
	else if (cls == "PRIEST") {
		player = new Priest(id, x, y, team);
	}
	else if (cls == "SCOUT") {
		player = new Scout(id, x, y, team);
	}
	else if (cls == "TANK") {
		player = new Tank(id, x, y, team);
	}
	players.push_back(player);
}
/**
 * The game ends when either of these happens:
 * - All barbarians die (knight victory)
 * - All knights die (barbarian victory)
 * - A barbarian gets to the square containing the chest (barbarian victory)
 * - maxTurnNumber of turns played (knight victory)
 *
 * If the game ends announce it py printing the reason, turn number and the victor
 * as in the following examples:
 *
 * Game ended at turn 13. All barbarians dead. Knight victory.
 * Game ended at turn 121. All knights dead. Barbarian victory.
 * Game ended at turn 52. Chest captured. Barbarian victory.
 * Game ended at turn 215. Maximum turn number reached. Knight victory.
 *
 * @return true if any of the above is satisfied, false otherwise
 *
 */
bool Game::isGameEnded() {
	int barbarianCount = 0;
	int knightCount = 0;
	
	for (int i = 0; i < players.size(); i++) {
			if (players[i]->getTeam() == BARBARIANS) {
				barbarianCount++;
			}
			else {
				knightCount++;
			}
	}
	if (knightCount == 0) {
		std::cout << "Game ended at turn " << turnNumber << ". All knights dead. Barbarian victory.";
		return true;
	}
	else if (barbarianCount == 0) {
		std::cout << "Game ended at turn " << turnNumber << ". All barbarians dead. Knight victory.";
		return true;
	}

	if (board.isPlayerOnCoordinate(board.getChestCoordinates())) {
		Player* a = board[board.getChestCoordinates()];
		if (a->getTeam() == BARBARIANS) {
			std::cout<< "Game ended at turn " << turnNumber << ". Chest captured. Barbarian victory.";
			return true;
		}
	}
	if (turnNumber == maxTurnNumber) {
		std::cout << "Game ended at turn " << turnNumber << ". Maximum turn number reached. Knight victory.";
		return true;
	}
	return false;
}
/**
   * Play a turn for each player.
   * Actions are taken in the order of ID numbers of players (player with
   * smaller ID acts first).
   * At the start of the turn it announces that the turn has started by printing
   * to stdout. Turn numbers starts with 1.
   * Ex: "Turn 13 has started."
   * Call playTurnForPlayer for every player.
   *
   */
void Game::playTurn() {

	turnNumber++;
	std::sort(players.begin(), players.end(), [](Player * p1, Player * p2) {return p1->getID() < p2->getID(); });
	std::vector<bool> ar(players.size());
	for (int i = 0; i < players.size(); i++) {
		ar[i] = players[i]->getflag();
	}
	for (int i = 0; i < players.size(); i++) {
		players[i]->setflag(false);
	}
	std::cout << "Turn " << turnNumber << " has started." << std::endl;
	for (int i = 0; i < players.size(); i++) {
		if (players[i]->isDead()) {
				std::cout << "Player " << players[i]->getBoardID() << " has died." << std::endl;
				players.erase(players.begin() + i);
				//ar.erase(ar.begin() + i);
				i--;
		}
		else {
			playTurnForPlayer(players[i]);
		}


	}

}
/**
   * Play a turn for the given player.
   * If the player is dead announce its death by printing the boardID of the player
   * as in "Player 07 died.". Remove that player from the board and release its resources.
   *
   * Each player has a goal list sorted by its priority for that player.
   * When a player plays a turn it iterates over its goal list and tries to take
   * an action. Valid actions are attack, move and heal. A player can take only
   * one action in a turn, and if there is no action it can take it stops and does nothing.
   * Before moving a player you must check if the coordinate to move is valid.
   * Meaning that, the coordinate is in the bounds of the board and there are no
   * players there.
   *
   * IMPORTANT NOTE: every usage of the word nearest is referencing smallest the manhattan
   * distance, which is formulated as (abs(x_1-x_2) + abs(y_1-y_2)). operator-
   * overloaded in Coordinate.h computes exactly that, so you can use that method to
   * calculate the distance between two coordinates.
   *
   * Below are the explanations for goals:
   *
   * ATTACK:
   *   - If there are any enemies in the attack range of the player attack to it.
   *     If there are more than 1 enemy in the range attack to the one with
   *     lowest ID. If there is no one to attack try the next goal.
   *
   * CHEST:
   *   - Move to the direction of the chest, if both vertical and horizontal moves
   *     are available, pick the horizontal one. If the horizontal move is blocked
   *     but the vertical move is not, move vertically. If all directions towards
   *     the chest is blocked try the next goal.
   *
   * TO_ENEMY:
   *   - Move towards the nearest enemy. If there are more than one enemies with the same distance
   *     move towards the one with the smallest ID. If both vertical and horizontal moves
   *     are available, pick the horizontal one. If an enemy is in the squares
   *     that the player can move or every move that brings the player closer to
   *     the selected enemy is blocked, try the next goal.
   *
   * TO_ALLY:
   *   - Move towards the nearest ally. If there are more than one allies with the same distance
   *     move towards the one with the smallest ID.  If both vertical and horizontal moves
   *     are available, pick the horizontal one. If an ally is in the squares
   *     that the player can move or every move that brings the player closer to
   *     the selected ally is blocked, try the next goal.
   *
   * HEAL:
   *   - If there are any allies in the healing range heal all of them. if there
   *     is no one to heal try the next goal.
   *
   *
   * @return the goal that the action was taken upon. NO_GOAL if no action was taken.
   */
bool Game::checkHorizontal(Player* player,Coordinate dir) {
	std::vector<Coordinate> al = player->getMoveableCoordinates();
	if (dir.x < 0) {
		if (board.isCoordinateInBoard(al[0]) && !board.isPlayerOnCoordinate(al[0])) {
			player->movePlayerToCoordinate(al[0]);
			return true;
		}
	}
	if (dir.x > 0) {
		if (board.isCoordinateInBoard(al[1]) && !board.isPlayerOnCoordinate(al[1])) {
			player->movePlayerToCoordinate(al[1]);
			return true;
		}
	}
	return false;

}
bool Game::checkVertical(Player* player,Coordinate dir) {
	Coordinate loc = player->getCoord();
	std::vector<Coordinate> al = player->getMoveableCoordinates();
	if (dir.y > 0) {
		if (board.isCoordinateInBoard(al[2]) && !board.isPlayerOnCoordinate(al[2])) {
			player->movePlayerToCoordinate(al[2]);
			return true;
		}
	}
	if (dir.y < 0) {
		if (board.isCoordinateInBoard(al[3]) && !board.isPlayerOnCoordinate(al[3])) {
			player->movePlayerToCoordinate(al[3]);
			return true;
		}
	}
	return false;
}
bool Game::checkDiagonal(Player* player,Coordinate dir) {
	std::vector<Coordinate> al = player->getMoveableCoordinates();
	if (dir.x > 0 && dir.y>0) { // sol üst
		if (board.isCoordinateInBoard(al[4]) && !board.isPlayerOnCoordinate(al[4])) {
			player->movePlayerToCoordinate(al[4]);
			return true;
		}
	}
	if (dir.x < 0 && dir.y > 0) {// sað üst
		if (board.isCoordinateInBoard(al[5]) && !board.isPlayerOnCoordinate(al[5])) {
			player->movePlayerToCoordinate(al[5]);
			return true;
		}
	}
	if (dir.x < 0 && dir.y < 0) {//sað alt
		if (board.isCoordinateInBoard(al[6]) && !board.isPlayerOnCoordinate(al[6])) {
			player->movePlayerToCoordinate(al[6]);
			return true;
		}
	}
	if (dir.x > 0 && dir.y < 0) {// sol alt
		if (board.isCoordinateInBoard(al[7]) && !board.isPlayerOnCoordinate(al[7])) {
			player->movePlayerToCoordinate(al[7]);
			return true;
		}
	}
	return false;
}
Goal Game::playTurnForPlayer(Player* player) {
	std::vector<Goal> a = player->getGoalPriorityList();
	int flag = 0;
	for (int i = 0; i < a.size(); i++) {
		flag = 0;
		if (a[i] == ATTACK) {
			int min = (int)1e9;
			std::vector<Coordinate> b = player->getAttackableCoordinates();
			for (int j = 0; j < b.size(); j++) {
				Player* gez;
				gez = board[b[j]];
				if (gez && gez->getTeam() != player->getTeam()) {
					min = min < gez->getID() ? min : gez->getID();
				}
			}
			if (min != 1e9) {
				for (int i = 0; i < players.size(); i++) {
					if (players[i]->getID() == min) {
						player->attack(players[i]);
						if (players[i]->isDead()) { players[i]->setflag(true); }
						return ATTACK;
					}
				}
			}
		}

		else if (a[i] == CHEST) {
			Coordinate loc = player->getCoord();
			Coordinate dir = Coordinate(loc.x - board.getChestCoordinates().x, loc.y - board.getChestCoordinates().y);// 1. negatifse saðda 2. negatifse yukarda 

			if (player->getClassAbbreviation() == "PR" || player->getClassAbbreviation() == "pr" || player->getClassAbbreviation() == "SC" || player->getClassAbbreviation() == "sc") {
				if (checkDiagonal(player, dir)) {
					return CHEST;
				}
				if (checkHorizontal(player, dir)) {
					return CHEST;
				}
				if (checkVertical(player, dir)) {
					return CHEST;
				}
			}
			else {
				if (checkHorizontal(player, dir)) {
					return CHEST;
				}
				if (checkVertical(player, dir)) {
					return CHEST;
				}
			}

		}
		else if (a[i] == TO_ENEMY) {
			std::vector<Coordinate> a = player->getMoveableCoordinates();
			for (int j = 0; j < a.size(); j++) {
				if (board.isPlayerOnCoordinate(a[j]) && board[a[j]]->getTeam() != player->getTeam() && board[a[j]]->getID() != player->getID()) {
					flag = 1;
					break;
				}


			}
			if (!flag) {
				Player* enemy = NULL;
				for (int i = 0; i < players.size(); i++) {
					if (player->getTeam() != players[i]->getTeam()  && players[i]->getID() != player->getID()) {
						if (enemy && enemy->getCoord()-player->getCoord() > players[i]->getCoord()-player->getCoord()) {
							enemy = players[i];
						}
						else if (!enemy) {
							enemy = players[i];
						}
						else if ((enemy && enemy->getCoord() - player->getCoord() == players[i]->getCoord() - player->getCoord())) {
							if (enemy->getID() > players[i]->getID()) {
								enemy =players[i];
							}
						}
					}
				}
				if (enemy) {
					Coordinate loc = player->getCoord();
					Coordinate dir = Coordinate(loc.x - enemy->getCoord().x, loc.y - enemy->getCoord().y);
					if (checkHorizontal(player, dir)) {
						return TO_ENEMY;
					}
					if (checkVertical(player, dir)) {
						return TO_ENEMY;
					}
				}
			}
		}
		else if (a[i] == TO_ALLY) {
			std::vector<Coordinate> a = player->getMoveableCoordinates();
			for (int j = 0; j < a.size(); j++) {
				if (board.isPlayerOnCoordinate(a[j]) && board[a[j]]->getTeam() == player->getTeam() && board[a[j]]->getID() != player->getID()) {
					flag = 1;
					break;
				}


			}
			if (!flag) {
				Player* enemy = NULL;
				for (int i = 0; i < players.size(); i++) {
					if (player->getTeam() == players[i]->getTeam() && players[i]->getID()!=player->getID()) {
						if (enemy && enemy->getCoord() - player->getCoord() > players[i]->getCoord() - player->getCoord()) {
							enemy = players[i];
						}
						else if (!enemy) {
							enemy = players[i];
						}
						else if ((enemy && enemy->getCoord() - player->getCoord() == players[i]->getCoord() - player->getCoord())) {
							if (enemy->getID() > players[i]->getID()) {
								enemy = players[i];
							}
						}
					}
				}
				
				if (enemy) {
					Coordinate loc = player->getCoord();
					Coordinate dir = Coordinate(loc.x - enemy->getCoord().x, loc.y - enemy->getCoord().y);
					if (checkDiagonal(player, dir)) {
						return TO_ALLY;
					}
					if (checkHorizontal(player, dir)) {
						return TO_ALLY;
					}
					if (checkVertical(player, dir)) {
						return TO_ALLY;
					}
				}
			}
		}
		else if (a[i] == HEAL) {
			std::vector<Coordinate> a = player->getHealableCoordinates();
			for (int i = 0; i < a.size(); i++) {
				if (board.isPlayerOnCoordinate(a[i]) && player->getTeam() == board[a[i]]->getTeam() ) {
					flag = 1;
					player->heal(board[a[i]]);
				}
			}
			if (flag) {
				flag = 0;
				return HEAL;
			}
		}
	}
}


