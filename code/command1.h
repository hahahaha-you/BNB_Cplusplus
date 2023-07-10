#pragma once
#include"common/map.h"

class playerCommand{
public:
	playerCommand(character* newPlagyer, Map* newMap) : player(newPlagyer), currentMap(newMap) {	}
	// true: player dead
	bool playerOperation();
	// change the position of player 
	void move();
	// The player uses weapon
	void fight();
	// the bomb has 3 state: not exist, ready to explode, explode
	bool changeBombState(int checkIndex);
	bool explosion(int bombDistance, int bombIndex, bool isRemoveBlock);
	~playerCommand(){}
private:
	character* player;
	Map* currentMap;
};  
