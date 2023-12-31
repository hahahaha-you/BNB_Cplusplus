#include"playercommand.h"

bool PlayerCommand::playerOperation() {
    if (player->getLive() == 0) return true;
    if (player->getOperation() < 4) this->move();
    else if (player->getOperation() == ATTACT)this->fight();
    int bombIndex = 0;
    while (1) {
        //check if the bomb is exploding
        //check all the bombs according to the bombIndex
        if (currentMap->getBomb(bombIndex)) {
            if (changeBombState(bombIndex)) bombIndex++;
            else continue;
            //the bomb is exploding
            if (currentMap->getBomb(bombIndex - 1)->getState() == 1) {
                //find the owner of the bomb and the distance of the explosion
                std::vector<characterWeapon*> playerWeapon;
                currentMap->getBomb(bombIndex - 1)->getOwner()->getWeapon(playerWeapon);
                int bombDistance = playerWeapon[0]->getDistance();
                if (explosion(bombDistance, bombIndex-1, false)) {
                    //the player dead
                    return true;
                }
            }
        }
        else break;
    }
    return false;
}

bool PlayerCommand::explosion(int bombDistance, int bombIndex, bool isRemoveBlock) {
    //get the coordinate of the player
    std::pair<double, double> currentCoordinate = player->getCoordinate();
    //get the coordinate of the bomb
    std::pair<int, int> bombCoordinate = currentMap->getBomb(bombIndex)->getCoordinate();
    //set explosion blocks according to the distance
    //check if the player is attacked by the bomb
    currentMap->getBlock(bombCoordinate.first, bombCoordinate.second)->upType(BOMB_EXPLOSION_CENTRAL);
    //check 4 directions
    for (int i = 1; i <= bombDistance; i++) {
        if (bombCoordinate.first + i >= currentMap->getColumnSize()) break;
        if (!(currentMap->getBlock(bombCoordinate.first + i, bombCoordinate.second)->upType(BOMB_EXPLOSION_RIGHT))) {
            if (isRemoveBlock) {
                currentMap->getBlock(bombCoordinate.first + i, bombCoordinate.second)->downType();
                continue;
            }
            break;
        }
        if (isRemoveBlock) {
            currentMap->getBlock(bombCoordinate.first + i, bombCoordinate.second)->downType();
        }
    }
    for (int i = 1; i <= bombDistance; i++) {
        if (bombCoordinate.first - i < 0 ) break;
        if (!(currentMap->getBlock(bombCoordinate.first - i, bombCoordinate.second)->upType(BOMB_EXPLOSION_LEFT))) {
            if (isRemoveBlock) {
                currentMap->getBlock(bombCoordinate.first - i, bombCoordinate.second)->downType();
                continue;
            }
            break;
        }
        if (isRemoveBlock) {
            currentMap->getBlock(bombCoordinate.first - i, bombCoordinate.second)->downType();
        }
    }
    for (int i = 1; i <= bombDistance; i++) {
        if (bombCoordinate.second + i >= currentMap->getRowSize()) break;
        if (!(currentMap->getBlock(bombCoordinate.first, bombCoordinate.second + i)->upType(BOMB_EXPLOSION_DOWN))) {
            if (isRemoveBlock) {
                currentMap->getBlock(bombCoordinate.first, bombCoordinate.second + i)->downType();
                continue;
            }
            break; 
        }
        if (isRemoveBlock) {
            currentMap->getBlock(bombCoordinate.first, bombCoordinate.second + i)->downType();
        }

    }
    for (int i = 1; i <= bombDistance; i++) {
        if (bombCoordinate.second - i < 0) break;
        if (!(currentMap->getBlock(bombCoordinate.first, bombCoordinate.second - i)->upType(BOMB_EXPLOSION_UP))) {
            if (isRemoveBlock) {
                currentMap->getBlock(bombCoordinate.first, bombCoordinate.second - i)->downType();
                continue;
            }
            break;
        }
        if (isRemoveBlock) {
            currentMap->getBlock(bombCoordinate.first, bombCoordinate.second - i)->downType();
        }
    }
    if (currentMap->getBlock(currentCoordinate.first, currentCoordinate.second)->getType() > 5) return player->hurt();
    if (currentCoordinate.second != (int)currentCoordinate.second) {
        if (currentMap->getBlock(currentCoordinate.first, currentCoordinate.second + 1)->getType() > 5) return player->hurt();
    }
    if (currentCoordinate.first != (int)currentCoordinate.first) {
        if (currentMap->getBlock(currentCoordinate.first + 1, currentCoordinate.second)->getType() > 5) return player->hurt();
        if (currentCoordinate.second != (int)currentCoordinate.second) {
            if (currentMap->getBlock(currentCoordinate.first + 1, currentCoordinate.second + 1)->getType() > 5) return player->hurt();
        }
    }
}

void PlayerCommand::move() {
    std::pair<double, double> newCoordinate = player->getCoordinate();
    switch (player->getOperation()) {
    case TURN_LEFT:
        if (newCoordinate.first == (int)newCoordinate.first ) newCoordinate.first -= player->getSpeed();
        else if (newCoordinate.first - (int)newCoordinate.first < player->getSpeed()-0.01) newCoordinate.first = (int)newCoordinate.first;
        else newCoordinate.first -= player->getSpeed();
        break;
    case TURN_RIGHT:
        if (newCoordinate.first == (int)newCoordinate.first){
            newCoordinate.first += player->getSpeed();
            break;
        }
        newCoordinate.first += player->getSpeed();
        if (newCoordinate.first - (int)newCoordinate.first < player->getSpeed()) newCoordinate.first = (int)newCoordinate.first;
        break;
    case TURN_UP:
        if (newCoordinate.second == (int)newCoordinate.second) newCoordinate.second -= player->getSpeed();
        else if (newCoordinate.second - (int)newCoordinate.second < player->getSpeed()) newCoordinate.second = (int)newCoordinate.second;
        else newCoordinate.second -= player->getSpeed();
        break;
    case TURN_DOWN:
        if (newCoordinate.second == (int)newCoordinate.second){
            newCoordinate.second += player->getSpeed();
            break;
        }
        newCoordinate.second += player->getSpeed();
        if (newCoordinate.second - (int)newCoordinate.second < player->getSpeed()) newCoordinate.second = (int)newCoordinate.second;
        break;
    default : break;
    }
    if (currentMap->getBlock(newCoordinate.first, newCoordinate.second)->getType() > 0
        && currentMap->getBlock(newCoordinate.first, newCoordinate.second)->getType() < 6) return;
    if (newCoordinate.second != (int)newCoordinate.second) {
        if (currentMap->getBlock(newCoordinate.first, newCoordinate.second + 1)->getType() > 0
            && currentMap->getBlock(newCoordinate.first, newCoordinate.second + 1)->getType() < 6) return;
    }
    if (newCoordinate.first != (int)newCoordinate.first) {
        if (currentMap->getBlock(newCoordinate.first + 1, newCoordinate.second)->getType() > 0
            && currentMap->getBlock(newCoordinate.first + 1, newCoordinate.second)->getType() < 6) return;
        if (newCoordinate.second != (int)newCoordinate.second) {
            if (currentMap->getBlock(newCoordinate.first + 1, newCoordinate.second + 1)->getType() > 0
                && currentMap->getBlock(newCoordinate.first + 1, newCoordinate.second + 1)->getType() < 6) return;
        }
    }
    if (newCoordinate.first < 0 || newCoordinate.first > currentMap->getColumnSize()-1) return;
    if (newCoordinate.second < 0 || newCoordinate.second > currentMap->getRowSize()-1) return;

    std::pair<int, int> bombCoordinate = player->getLastBombCoordinate();
    //check if the position has a bomb

    player->move(newCoordinate);
}

void PlayerCommand::fight() {
    std::pair<int, int> currentCoordinate;
    currentCoordinate.first = player->getCoordinate().first + 0.5;
    currentCoordinate.second = player->getCoordinate().second + 0.5;
    std::vector<characterWeapon*> currentWeapon;
    player->getWeapon(currentWeapon);
    if (currentWeapon.size() == 1) {
        if(player->getLastBombCoordinate().first == -1)
            currentMap->setBomb(currentCoordinate, player);
    }
}

bool PlayerCommand::changeBombState(int checkIndex){
    if (currentMap->getBomb(checkIndex) == nullptr) return false;
    double passedTime = clock() - currentMap->getBomb(checkIndex)->getTime();
    if (currentMap->getBomb(checkIndex)->getState() == 0) {
        if (passedTime > 400) currentMap->getBlock(currentMap->getBomb(checkIndex)->getCoordinate().first, currentMap->getBomb(checkIndex)->getCoordinate().second)->upType(BOMB_READY);
    }
    if (passedTime > 1000) {
        currentMap->getBomb(checkIndex)->changeState(currentMap->getBomb(checkIndex)->getState() + 1);
        currentMap->getBomb(checkIndex)->setTime();
    }

    if (currentMap->getBomb(checkIndex)->getState() > 1) {
        std::vector<characterWeapon*> playerWeapon;
        currentMap->getBomb(checkIndex)->getOwner()->getWeapon(playerWeapon);
        int bombDistance = playerWeapon[0]->getDistance();
        explosion(bombDistance, checkIndex, true);
        currentMap->getBlock(currentMap->getBomb(checkIndex)->getCoordinate().first, currentMap->getBomb(checkIndex)->getCoordinate().second)->downType();
        currentMap->getBomb(checkIndex)->getOwner()->deleteLastBomb();
        currentMap->deleteBomb();

        return false;
    }
    return true;
}


