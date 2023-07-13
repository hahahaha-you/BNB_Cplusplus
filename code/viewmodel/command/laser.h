#pragma once
#include"map.h"
#include<utility>
class Laser{
public:
	Laser(Character* newPlayer, Map* newMap);
    bool pickUpLaser();
    void explosionLaser();
    bool explosionPlayer(Character * explodePlayer);
    void recover();
    bool changeState(int checkIndex);
	~Laser(){}
private:
	Character* player;
	Map* currentMap;
    std::pair<int,int> coordinate;
    Direction playerDirection;
};  
