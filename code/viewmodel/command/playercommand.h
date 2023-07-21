#pragma once
#include"../../common/map.h"

class PlayerCommand{
public:
    PlayerCommand()=default;
    void initial(std::pair<double,double> coordinate, Map *map) {
        currentMap = map;
        player = new Character(coordinate,0.07);
    }
    Map* getMap(){return currentMap;}
    Character* getPlayer(){return player;}
	// true: player dead
	bool playerOperation();
	// change the position of player 
	void move();
	// The player uses weapon
	void fight();
	// the bomb has 3 state: not exist, ready to explode, explode
	bool changeBombState(int checkIndex);
	bool explosion(int bombDistance, int bombIndex, bool isRemoveBlock);
	~PlayerCommand(){}
private:
    Character *player;
	Map *currentMap;
};  
