#pragma once
#include"viewmodel.h"

void CommandViewModel :: commandSlots(int playerNum, int opr){
    if(opr==0)playerControl[playerNum]->getPlayer()->updateOperation(TURN_LEFT);
	else if(opr==1)playerControl[playerNum]->getPlayer()->updateOperation(TURN_RIGHT);
    else if(opr==2)playerControl[playerNum]->getPlayer()->updateOperation(TURN_UP);
    else if(opr==3)playerControl[playerNum]->getPlayer()->updateOperation(TURN_DOWN);
    else if(opr==4)playerControl[playerNum]->getPlayer()->updateOperation(ATTACT);
    else if(opr==5)playerControl[playerNum]->getPlayer()->updateOperation(INVALID_OPERATION);
    playerControl[playerNum]->playerOperation();
    playerWeapons[playerNum]->changeState();
    return;
}

void CommandViewModel :: initial(){
    map = new Map();
    map->initial();
    PlayerCommand* p1 = new PlayerCommand();
    p1->initial(std::make_pair<double, double>(0,0), map);
    PlayerCommand* p2 = new PlayerCommand();
    p2->initial(std::make_pair<double, double>(11,11), map);
    playerControl.push_back(p1);
    playerControl.push_back(p2);
    Character * player1 = getPlayerControl()[0]->getPlayer();
    Character * player2 = getPlayerControl()[1]->getPlayer();
    PropCommand * L1 = new PropCommand(player1,player2,map);
    //L1->changeState();
    playerWeapons.push_back(L1);
    PropCommand * L2 = new PropCommand(player2,player1,map);
    //L2->changeState();
    playerWeapons.push_back(L2);
    //initial
    std::ifstream  fin;

    fin.open ("../resources/maps/laserMap.txt" ,std::ios::in);
    int j=0,k=0,m=0,pID=0;        //different IDs of different props
    for(int i = 0; i < map->getColumnSize()*map->getRowSize(); i++){
        char ch;
        fin >> ch;
        if (ch == '0')
            continue;
        else if (ch == ' ' || ch == '\n') i--;
        else if(map->getBlock(i%map->getColumnSize(),i/map->getColumnSize())->getType()==BLOCK_CAN_BE_DESTROYED_1) {
            propType currentProp;
            if (ch == '1') {
                currentProp = LASER;
                pID=j++;
            }else if (ch == '2'){
                currentProp = SPEEDUP;
                pID=k++;
            }else if (ch == '3'){
                currentProp = BIGBOMB;
                pID=m++;
            }
            Prop * p = new Prop(std::make_pair(i%map->getColumnSize(),i/map->getColumnSize()),currentProp,pID);
            map->addProp(p);
        }
    }
}

