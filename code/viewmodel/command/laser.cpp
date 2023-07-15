#include"laser.h"

Laser::Laser(Character* newPlayer,Character * newOtherPlayer, Map* newMap) : player(newPlayer),otherPlayer(newOtherPlayer), currentMap(newMap), coordinate(std::pair<int,int>(-1,-1)),state(WITHOUT)
{
}

bool Laser::pickUp(){
    std::pair<int,int> playerCoordinate =std::make_pair((int)player->getCoordinate().first,(int)player->getCoordinate().second);
    for(int i=0;i<currentMap->getPropNumber();i++){
        Prop * propPick=currentMap->getProp(i);
        if(playerCoordinate==propPick->getCoordinate()){
            if(propPick->pickUpProp()) {
                if(propPick->getType()==LASER){
                    player->setBomb("Laser");
                    player->setBomb("Laser");
                    type = LASER;
                    state = PICKUP;
                    return true;
                }else if(propPick->getType()==SPEEDUP){
//                    type = SPEEDUP;
//                    state = PICKUP;
//                    player->setBomb("Speedup");
                    player->changeSpeed(player->getSpeed()*2);
//                    currentMap->setBomb(coordinate,player);
//                    currentMap->getBomb()->setTime();
                }else if(propPick->getType()==BIGBOMB) {
                    std::vector <characterWeapon*> playerWeapon;
                    player->getWeapon(playerWeapon);
                    playerWeapon[0]->changeDistance();
                }
                
                return false;
            }
            
        }
    }
    return false;
}


bool Laser::explosionLaser(Character * explodePlayer){
    //get the coordinate of the bomb
//	std::pair<double, double> currentCoordinate = player->getCoordinate();
	//get the coordinate of the player
	// std::pair<int, int> otherPlayerCoordinate = std::pair<int,int>((int)(otherPlayer->getCoordinate().first),(int)(otherPlayer->getCoordinate().second));
//    std::cout<<"a";
//    player->hurt();return true;
            //bomb_index
    //currentMap->setBomb(coordinate,player);
//    player->hurt();return true;
//    if(!currentMap->getBomb())player->hurt();
//    if(currentMap->getBombNumber()==0){player->hurt();return true;}

//    std::cout<<"B";
//    player->hurt();return true;

//    std::cout<<"c";
    int ret=false;
    std::pair<int,int> PlayerCoordinate = std::pair<int,int>((int)explodePlayer->getCoordinate().first, (int)explodePlayer->getCoordinate().second);
//    std::cout<<"d";
//    player->hurt();return true;
    switch (playerDirection)
    {
    case LEFT:
        currentMap->getBlock(coordinate.first,coordinate.second)->upType(LASER_EXPLOSION_CENTRAL_LEFT);
        for (int i = coordinate.first-1; i >=0 ; i--) {
            currentMap->getBlock(i, coordinate.second)->explodeType(LASER_EXPLOSION_LEFT);
            if (PlayerCoordinate == std::make_pair(i,coordinate.second)) {
                if (explodePlayer->hurt()) {
                    ret = true;
                }
            }
        }
        break;
    case RIGHT:
        currentMap->getBlock(coordinate.first,coordinate.second)->upType(LASER_EXPLOSION_CENTRAL_RIGHT);
        for (int i = coordinate.first+1; i <currentMap->getColumnSize() ; i++) {
            currentMap->getBlock(i, coordinate.second)->explodeType(LASER_EXPLOSION_RIGHT);
            if (PlayerCoordinate == std::make_pair(i,coordinate.second)) {
                if (explodePlayer->hurt()) {
                    ret = true;
                }
            }
        }
        break;
    case UP:
        currentMap->getBlock(coordinate.first,coordinate.second)->upType(LASER_EXPLOSION_CENTRAL_UP);
        for (int i = coordinate.second-1; i >=0 ; i--) {
            currentMap->getBlock(coordinate.first, i)->explodeType(LASER_EXPLOSION_UP);
            if (PlayerCoordinate == std::make_pair(coordinate.first, i)) {
                if (explodePlayer->hurt()) {
                    ret = true;
                }
            }
        }
        break;
    case DOWN:
        currentMap->getBlock(coordinate.first,coordinate.second)->upType(LASER_EXPLOSION_CENTRAL_DOWN);
        for (int i = coordinate.second+1; i <currentMap->getRowSize() ; i++) {
            currentMap->getBlock(coordinate.first, i)->explodeType(LASER_EXPLOSION_DOWN);
            if (PlayerCoordinate == std::make_pair(coordinate.first, i)) {       
                if (explodePlayer->hurt()) {
                    ret = true;
                }
            }
        }
        break;
    default:
        break;
    }
    return ret;
}

void Laser::recover(){
    for(int i=currentMap->getColumnSize()*currentMap->getRowSize()-1;i>=0;i--){
        currentMap->getBlock(i%currentMap->getColumnSize(),i/currentMap->getRowSize())->recoverType();
    }
}


bool Laser::changeState(){
    switch (state)
    {
    case WITHOUT :
    {
        if(pickUp()){
            state = PICKUP;
        }
        break;
    }
    case PICKUP :
    {
        pickUp();
        if(player->getOperation()==ATTACT){
            state = EXCITE;
            playerDirection = player->getDirection();
            coordinate = std::pair<int,int>((int)(player->getCoordinate().first),(int)(player->getCoordinate().second));
            currentMap->setBomb(coordinate,player);
            currentMap->getBomb()->setTime();
            if(explosionLaser(player) ){
                return false;}//|| explosionLaser(otherPlayer)) return false;
        }
        break;
    }
    case EXCITE:
    {
        if(explosionLaser(player) || explosionLaser(otherPlayer)) return false;
        double passedTime = clock() - currentMap->getBomb()->getTime();
//        player->hurt();return true;
        if(passedTime > 950){
//            player->hurt();return true;
            recover();
//            player->hurt();return true;
            player->deleteLastWeapon();
//            player->hurt();return true;
            currentMap->deleteWeapon();
//            player->hurt();return true;
            std::vector<characterWeapon*> playerWeapon;
            player->getWeapon(playerWeapon);
//            if(playerWeapon.size()==2){player->hurt();return true;}
            std::string weaponID=playerWeapon.back()->getID();
            if(weaponID!="bomb"&&weaponID=="Laser"){
                state = PICKUP;
//                if(weaponID=="Laser"){
//                   player->hurt();return true;
//                    type = LASER;
//                }else if (weaponID == "SPEEDUP"){
//                    type = SPEEDUP;
//                }
            }else {
                state = WITHOUT;
            }
        }
        break;
    }
    default:
        break;
    }
    return true;
}

