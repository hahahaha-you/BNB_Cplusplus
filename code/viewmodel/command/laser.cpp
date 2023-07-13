#include"Laser.h"

Laser::Laser(Character* newPlayer, Map* newMap) : player(newPlayer), currentMap(newMap), coordinate(std::pair<int,int>(-1,-1)) {
    //initial
    std::ifstream  fin;
    fin.open ("../../bombtest/resources/maps/laserMap.txt" ,std::ios::in);
    int j=0,k=0,m=0;
    for(int i = 0; i < currentMap->getColumnSize()*currentMap->getRowSize(); i++){
        char ch;
        fin >> ch;
        if (ch == '0') continue;
        else if (ch == '1') {
            if(currentMap->getBlock(i%currentMap->getColumnSize(),i/currentMap->getColumnSize())->getType()==BLOCK_CAN_BE_DESTROYED_1) {
                Prop * p = new Prop(std::make_pair(i%currentMap->getColumnSize(),i/currentMap->getColumnSize()),LASER,j);
                j++;
                currentMap->addProp(p);
            }
        }
        else if (ch == ' ' || ch == '\n') i--;
    }
}

bool Laser::pickUpLaser(){
    std::pair<int,int> playerCoordinate =std::make_pair((int)player->getCoordinate().first,(int)player->getCoordinate().second);
    for(int i=0;i<currentMap->getPropNumber();i++){
        if(playerCoordinate==currentMap->getProp(i)->getCoordinate()){
            if(currentMap->getProp(i)->pickUpProp()) {
                player->setBomb("Laser");
                player->setBomb("Laser");
                return true;
            }
            
        }
    }
    return false;
}

void Laser::explosionLaser(){
    //get the coordinate of the bomb
	std::pair<double, double> currentCoordinate = player->getCoordinate();
	//get the coordinate of the player
	// std::pair<int, int> otherPlayerCoordinate = std::pair<int,int>((int)(otherPlayer->getCoordinate().first),(int)(otherPlayer->getCoordinate().second));
	coordinate = std::pair<int,int>((int)(player->getCoordinate().first),(int)(player->getCoordinate().second));          //bomb_index
    currentMap->setBomb(coordinate,player);
    currentMap->getBomb()->setTime();

    playerDirection = player->getDirection();
    switch (playerDirection)
    {
    case LEFT:
        currentMap->getBlock(coordinate.first,coordinate.second)->upType(LASER_EXPLOSION_CENTRAL_LEFT);
        for (int i = coordinate.first-1; i >=0 ; i--) {
            currentMap->getBlock(i, coordinate.second)->explodeType(LASER_EXPLOSION_LEFT);
        }
        break;
    case RIGHT:
        currentMap->getBlock(coordinate.first,coordinate.second)->upType(LASER_EXPLOSION_CENTRAL_RIGHT);
        for (int i = coordinate.first+1; i <currentMap->getColumnSize() ; i++) {
            currentMap->getBlock(i, coordinate.second)->explodeType(LASER_EXPLOSION_RIGHT);
        }
        break;
    case UP:
        currentMap->getBlock(coordinate.first,coordinate.second)->upType(LASER_EXPLOSION_CENTRAL_UP);
        for (int i = coordinate.second-1; i >=0 ; i--) {
            currentMap->getBlock(coordinate.first, i)->upType(LASER_EXPLOSION_UP);
        }
        break;
    case DOWN:
        currentMap->getBlock(coordinate.first,coordinate.second)->upType(LASER_EXPLOSION_CENTRAL_DOWN);
        for (int i = coordinate.second+1; i <currentMap->getRowSize() ; i++) {
            currentMap->getBlock(coordinate.first, i)->upType(LASER_EXPLOSION_DOWN);
        }
        break;
    default:
        break;
    }   
}

bool Laser::explosionPlayer(Character * explodePlayer){
    int ret=false;
    std::pair<int,int> PlayerCoordinate = std::pair<int,int>((int)explodePlayer->getCoordinate().first, (int)explodePlayer->getCoordinate().second);
    switch (playerDirection)
    {
    case LEFT:
        for (int i = coordinate.first-1; i >=0 ; i--) {
            if (PlayerCoordinate == std::make_pair(i,coordinate.second)) {
                if (explodePlayer->hurt()) {
                    ret = true;
                }
            }
        }
        break;
    case RIGHT:
        for (int i = coordinate.first+1; i <currentMap->getColumnSize() ; i++) {
            if (PlayerCoordinate == std::make_pair(i,coordinate.second)) {
                if (explodePlayer->hurt()) {
                    ret = true;
                }
            }
        }
        break;
    case UP:
        for (int i = coordinate.second-1; i >=0 ; i--) {
            if (PlayerCoordinate == std::make_pair(coordinate.first, i)) {
                if (explodePlayer->hurt()) {
                    ret = true;
                }
            }
        }
        break;
    case DOWN:
        for (int i = coordinate.second+1; i <currentMap->getRowSize() ; i++) {
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
    //player->setDirection
    switch (playerDirection)
    {
    case LEFT:
        for (int i = coordinate.first-1; i >=0 ; i--) {
            currentMap->getBlock(i, coordinate.second)->recoverType();
        }
        break;
    case RIGHT:
        for (int i = coordinate.first+1; i <currentMap->getColumnSize() ; i++) {
            currentMap->getBlock(i, coordinate.second)->recoverType();
        }
        break;
    case UP:
        for (int i = coordinate.second-1; i >=0 ; i--) {
            currentMap->getBlock(coordinate.first, i)->recoverType();
        }
        break;
    case DOWN:
        for (int i = coordinate.second+1; i <currentMap->getRowSize() ; i++) {
            currentMap->getBlock(coordinate.first, i)->recoverType();
        }
        break;
    default:
        break;
    }
}


bool Laser::changeState(int checkIndex){
	if (currentMap->getBomb(checkIndex) == nullptr) return false;
	double passedTime = clock() - currentMap->getBomb(checkIndex)->getTime();
	if (currentMap->getBomb(checkIndex)->getState() == 1) {
        if(passedTime > 1000){
            player->deleteLastWeapon();
            currentMap->deleteWeapon();
            recover();
            return true;
        }
    }
    return false;
}



