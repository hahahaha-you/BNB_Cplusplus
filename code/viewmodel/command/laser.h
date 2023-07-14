#pragma once
#include"../../common/map.h"
#include<utility>

enum laserState{
    WITHOUT,
    PICKUP,
    WAITING,
    EXCITE
};

class Laser{
public:
	Laser(Character* newPlayer, Map* newMap);
    bool pickUp();
    bool explosionLaser(Character * explodePlayer);
    void recover();
    bool changeState();
	~Laser(){}
private:
	Character* player;
    Character * otherPlayer;
	Map* currentMap;
    std::pair<int,int> coordinate;
    Direction playerDirection;
    laserState state; 
    propType type;
};  
