#pragma once
#include"map.h"

class playerCommand{
public:
	playerCommand(character* newPlagyer, map* newMap) : player(newPlagyer), currentMap(newMap) {	}
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
	map* currentMap;
};  
