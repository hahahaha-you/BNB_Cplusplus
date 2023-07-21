#pragma once
#include"../../common/map.h"
#include<utility>

enum laserState{
    WITHOUT,
    PICKUP,
    WAITING,
    EXCITE
};

class PropCommand{
public:
    PropCommand(Character* newPlayer,Character * newOtherPlayer, Map* newMap);
    bool pickUp();
    bool explosionLaser(Character * explodePlayer);
    void recover();
    bool changeState();
	~PropCommand(){}
private:
	Character* player;
    Character * otherPlayer;
	Map* currentMap;
    std::pair<int,int> coordinate;
    Direction playerDirection;
    laserState state; 
    propType type;
};  
