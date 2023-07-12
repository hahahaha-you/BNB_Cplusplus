#pragma once
#include"commandviewmodel.h"

void CommandViewModel :: commandSlots(int playerNum, int opr){
    if(opr==0)playerControl[playerNum]->getPlayer()->updateOperation(TURN_LEFT);
	else if(opr==1)playerControl[playerNum]->getPlayer()->updateOperation(TURN_RIGHT);
    else if(opr==2)playerControl[playerNum]->getPlayer()->updateOperation(TURN_UP);
    else if(opr==3)playerControl[playerNum]->getPlayer()->updateOperation(TURN_DOWN);
    else if(opr==4)playerControl[playerNum]->getPlayer()->updateOperation(ATTACT);
    else if(opr==5)playerControl[playerNum]->getPlayer()->updateOperation(INVALID_OPERATION);
    playerControl[playerNum]->playerOperation();
    return;
}

void CommandViewModel :: initial(){
    map = new Map();
    map->initial();
    playerCommand* p1 = new playerCommand();
    p1->initial(std::make_pair<double, double>(0,0), map);
    playerCommand* p2 = new playerCommand();
    p2->initial(std::make_pair<double, double>(11,11), map);
    playerControl.push_back(p1);
    playerControl.push_back(p2);
}

