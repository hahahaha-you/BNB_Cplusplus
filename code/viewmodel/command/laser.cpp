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
                }else if(propPick->getType()==SPEEDUP){
                    type = SPEEDUP;
                    state = PICKUP;
                    player->setBomb("Speedup");
                    player->changeSpeed(player->getSpeed()*2);
                    currentMap->setBomb(coordinate,player);
                    currentMap->getBomb()->setTime();
                }else if(propPick->getType()==BIGBOMB) {
                    std::vector <characterWeapon*> playerWeapon;
                    player->getWeapon(playerWeapon);
                    playerWeapon[0]->changeDistance();
                }
                
                return true;
            }
            
        }
    }
    return false;
}


bool Laser::explosionLaser(Character * explodePlayer){
    //get the coordinate of the bomb
	std::pair<double, double> currentCoordinate = player->getCoordinate();
	//get the coordinate of the player
	// std::pair<int, int> otherPlayerCoordinate = std::pair<int,int>((int)(otherPlayer->getCoordinate().first),(int)(otherPlayer->getCoordinate().second));
	coordinate = std::pair<int,int>((int)(player->getCoordinate().first),(int)(player->getCoordinate().second));          //bomb_index
    //currentMap->setBomb(coordinate,player);
    currentMap->getBomb()->setTime();

    playerDirection = player->getDirection();
    int ret=false;
    std::pair<int,int> PlayerCoordinate = std::pair<int,int>((int)explodePlayer->getCoordinate().first, (int)explodePlayer->getCoordinate().second);
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
            currentMap->getBlock(coordinate.first, i)->upType(LASER_EXPLOSION_UP);
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
            currentMap->getBlock(coordinate.first, i)->upType(LASER_EXPLOSION_DOWN);
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
        if(type == SPEEDUP) {
            double passedTime = clock() - currentMap->getBomb()->getTime();
            if(passedTime > 1000){
                player->changeSpeed(player->getSpeed()/2);
                player->deleteLastWeapon();
                currentMap->deleteWeapon();
                std::vector<characterWeapon*> playerWeapon;
                player->getWeapon(playerWeapon);
                std::string weaponID=playerWeapon.back()->getID();
                if(weaponID!="bomb"){
                    state = PICKUP;
                    if(weaponID=="Laser"){
                        type = LASER;
                    }else if (weaponID == "SPEEDUP"){
                        type = SPEEDUP;
                    }
                }else {
                    state = WITHOUT;
                }
            }
        }else {
            pickUp();
            std::vector<characterWeapon*> playerWeapon;
            player->getWeapon(playerWeapon);
            if(player->getOperation()==ATTACT && playerWeapon.back()->getID()!="bomb"){
                state = EXCITE;
            }
        }
        break;
    }
    case EXCITE:
    {
        if(explosionLaser(player) || explosionLaser(otherPlayer)) return false;
        double passedTime = clock() - currentMap->getBomb()->getTime();
        if(passedTime > 1000){
            recover();
            player->deleteLastWeapon();
            currentMap->deleteWeapon();
            std::vector<characterWeapon*> playerWeapon;
            player->getWeapon(playerWeapon);
            std::string weaponID=playerWeapon.back()->getID();
            if(weaponID!="bomb"){
                state = PICKUP;
                if(weaponID=="Laser"){
                    type = LASER;
                }else if (weaponID == "SPEEDUP"){
                    type = SPEEDUP;
                }
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

