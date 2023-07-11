#pragma once
#include<QObject>
#include"common/map.h"

class playerCommand : public QObject{
    Q_OBJECT
public slots:
    void commandSlots(int opr){
        if(opr==0)player->updateOperation(TURN_LEFT);
        else if(opr==1)player->updateOperation(TURN_RIGHT);
        else if(opr==2)player->updateOperation(TURN_UP);
        else if(opr==3)player->updateOperation(TURN_DOWN);
        else if(opr==4)player->updateOperation(ATTACT);
        else if(opr==5)player->updateOperation(INVALID_OPERATION);
        playerOperation();
        return;
    }
public:
    playerCommand(Character *player,Map *map){initial(player->getCoordinate(),map);}
    void initial(std::pair<double,double> coordinate,Map *map) {
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
	~playerCommand(){}
private:
    Character* player;
	Map* currentMap;
};  
