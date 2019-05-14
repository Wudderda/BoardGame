#include"InputParser.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
/**
   * Parse the initial parameters of the game from stdin.
   * The input will be as follows.
   * First line contains the size of the board.
   * Second line contains the coordinates of the chest.
   * Third line contains the maximum turn number for the game.
   * Fourth line contains the number of players, P.
   * Each of the next P lines contains a description for a player as follows.
   * ID of the player, class of the player, team of the player, x coordinate, y coordinate, .
   * Call the addPlayer method of the Game class to add the players.
   * Example input:
   * 6
   * 3 3
   * 100
   * 2
   * 12 ARCHER BARBARIAN 3 5
   * 11 FIGHTER KNIGHT 1 1
   *
   * @returns Pointer to the Dynamically allocated Game object
   */
Game* InputParser::parseGame() {
	unsigned int size;
	int x, y;
	int maxturn = 0;
	int i = 0;
	std::cin >> size;
	std::cin >> x >> y;
	std::cin >> maxturn;
	std::cin >> i;
	Game* a = new Game(maxturn,size,Coordinate(x,y));
	int id;
	std::string type;
	std::string clas;
	int x2, y2;
	for (int j = 0; j < i; j++) {
		std::cin >> id >> type >> clas >> x2 >> y2;
		Team b = clas == "BARBARIAN" ? BARBARIANS : KNIGHTS;
		a->addPlayer(id, x2, y2, b, type);
	}
	return a;
}