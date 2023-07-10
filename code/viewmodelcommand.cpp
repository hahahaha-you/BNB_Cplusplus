#include "viewmodelcommand.h"

bool playerCommand::playerOperation() {
	if (player->getOperation() == INVALID_OPERATION) return false;
	else if (player->getOperation() < 4) this->move();
	else this->fight();
	int bombIndex = 0;
	while (1) {
		//check if the bomb is exploding
		//check all the bombs according to the bombIndex
		if (currentMap->getBomb(bombIndex)) {
			if (changeBombState(bombIndex)) bombIndex++;
			//the bomb is exploding
			if (currentMap->getBomb(bombIndex)->getState() == 1) {
				//find the owner of the bomb and the distance of the explosion
				std::vector<characterWeapon*> playerWeapon;
				currentMap->getBomb(bombIndex)->getOwner()->getWeapon(playerWeapon);
				int bombDistance = playerWeapon[0]->getDistance();
				if (explosion(bombDistance, bombIndex, false)) {
					//the player dead
					return true;
				}
			}
		}
		else break;
	}
	return false;
}

bool playerCommand::explosion(int bombDistance, int bombIndex, bool isRemoveBlock) {
	//get the coordinate of the bomb
	std::pair<double, double> currentCoordinate = player->getCoordinate();
	//get the coordinate of the player
	std::pair<int, int> playerCoordinate((int)currentCoordinate.first,(int)currentCoordinate.second);
	std::pair<int, int> bombCoordinate = currentMap->getBomb(bombIndex)->getCoordinate();
	//set explosion blocks according to the distance
	//check if the player is attacked by the bomb
	currentMap->getBlock(bombCoordinate.first, bombCoordinate.second)->upType(BOMB_EXPLOSION);
	//check 4 way
	for (int i = 1; i <= bombDistance; i++) {
		if (bombCoordinate.first + i >= currentMap->getColumnSize()) break;
		if (!(currentMap->getBlock(bombCoordinate.first + i, bombCoordinate.second)->upType(BOMB_EXPLOSION))) {
			if (isRemoveBlock) {
				currentMap->getBlock(bombCoordinate.first + i, bombCoordinate.second)->downType();
			}
			break;
		}
		bombCoordinate.first += i;
		if (playerCoordinate == bombCoordinate) {
			bombCoordinate.first -= i;
			if (player->hurt()) {
				return true;
			}
		}
	}
	for (int i = 1; i <= bombDistance; i++) {
		if (bombCoordinate.first - i < 0 ) break;
		if (!(currentMap->getBlock(bombCoordinate.first - i, bombCoordinate.second)->upType(BOMB_EXPLOSION))) {
			if (isRemoveBlock) {
				currentMap->getBlock(bombCoordinate.first - i, bombCoordinate.second)->downType();
			}
			break;
		}
		bombCoordinate.first -= i;
		if (playerCoordinate == bombCoordinate) {
			bombCoordinate.first += i;
			if (player->hurt()) {
				return true;
			}
		}
	}
	for (int i = 1; i <= bombDistance; i++) {
		if (bombCoordinate.second + i >= currentMap->getRowSize()) break;
		if (!(currentMap->getBlock(bombCoordinate.first, bombCoordinate.second + i)->upType(BOMB_EXPLOSION))) {
			if (isRemoveBlock) {
				currentMap->getBlock(bombCoordinate.first, bombCoordinate.second + i)->downType();
			}
			break;
		}
		if (isRemoveBlock) {
			currentMap->getBlock(bombCoordinate.first, bombCoordinate.second + i)->downType();
		}
		bombCoordinate.second += i;
		if (playerCoordinate == bombCoordinate) {
			bombCoordinate.second -= i;
			if (player->hurt()) {
				return true;
			}
		}
	}
	for (int i = 1; i <= bombDistance; i++) {
		if (bombCoordinate.second - i < 0) break;
		if (!(currentMap->getBlock(bombCoordinate.first, bombCoordinate.second - i)->upType(BOMB_EXPLOSION))) {
			if (isRemoveBlock) {
				currentMap->getBlock(bombCoordinate.first, bombCoordinate.second - i)->downType();
			}
			break;
		}
		bombCoordinate.second -= i;
		if (playerCoordinate == bombCoordinate) {
			bombCoordinate.second += i;
			if (player->hurt()) {
				return true;
			}
		}
	}
}

void playerCommand::move() {
	std::pair<double, double> newCoordinate = player->getCoordinate();
	switch (player->getOperation()) {
	case TURN_LEFT:
		if (newCoordinate.first - (int)newCoordinate.first < player->getSpeed())newCoordinate.first = (int)newCoordinate.first;
		else newCoordinate.first -= player->getSpeed();
		break;
	case TURN_RIGHT:
		newCoordinate.first += player->getSpeed();
		if (newCoordinate.first - (int)newCoordinate.first < player->getSpeed())newCoordinate.first = (int)newCoordinate.first;
		break;
	case TURN_UP:
		if (newCoordinate.second - (int)newCoordinate.second < player->getSpeed()) newCoordinate.second = (int)newCoordinate.second;
		else newCoordinate.second -= player->getSpeed();
		break;
	case TURN_DOWN:
		newCoordinate.second += player->getSpeed();
		if (newCoordinate.second - (int)newCoordinate.second < player->getSpeed()) newCoordinate.second = (int)newCoordinate.second;
		break;
	default : break;	
	}
	if (currentMap->getBlock(newCoordinate.first, newCoordinate.second)->getType() != ROAD) return;
	if (newCoordinate.second != (int)newCoordinate.second) {
		if (currentMap->getBlock(newCoordinate.first, newCoordinate.second + 1)->getType() != ROAD) return;
	}
	if (newCoordinate.first != (int)newCoordinate.first) {
		if (currentMap->getBlock(newCoordinate.first + 1, newCoordinate.second)->getType() != ROAD) return;
		if (newCoordinate.second != (int)newCoordinate.second) {
			if (currentMap->getBlock(newCoordinate.first + 1, newCoordinate.second + 1)->getType() != ROAD) return;
		}
	}
	if (newCoordinate.first < 0 || newCoordinate.first >= currentMap->getColumnSize()) return;
	if (newCoordinate.second < 0 || newCoordinate.second >= currentMap->getRowSize()) return;
	
	std::pair<int, int> bombCoordinate = player->getLastBombCoordinate();
	//check if the position has a bomb
	/*
	int checkIndex = 0;
	if (bombCoordinate.first != -1) {
		while (1) {
			if (currentMap->getBomb(checkIndex) == nullptr) break;
			if (((int)newCoordinate.first == currentMap->getBomb(checkIndex)->getCoordinate().first) &&
				((int)newCoordinate.second == currentMap->getBomb(checkIndex)->getCoordinate().second)) break;
			checkIndex++;
		}
		if (currentMap->getBomb(checkIndex) == nullptr) player->deleteLastBomb();
	}
	checkIndex = 0;
	if (bombCoordinate.first == -1) {
		while (1) {
			if (currentMap->getBomb(checkIndex) == nullptr) break;
			if (((int)newCoordinate.first == currentMap->getBomb(checkIndex)->getCoordinate().first) &&
				((int)newCoordinate.second == currentMap->getBomb(checkIndex)->getCoordinate().second)) return;
			checkIndex++;
		}
	}
	*/
	player->move(newCoordinate);
}

void playerCommand::fight() {
	std::pair<int, int> currentCoordinate = player->getCoordinate();
	std::vector<characterWeapon*> currentWeapon;
	player->getWeapon(currentWeapon);
	if (currentWeapon.size() == 1) {
		currentMap->setBomb(currentCoordinate, player);
	}
}

bool playerCommand::changeBombState(int checkIndex){
	if (currentMap->getBomb(checkIndex) == nullptr) return false;
	double passedTime = clock() - currentMap->getBomb(checkIndex)->getTime();
	if (currentMap->getBomb(checkIndex)->getState() == 0) {
		if (passedTime > 500) currentMap->getBlock(currentMap->getBomb(checkIndex)->getCoordinate().first, currentMap->getBomb(checkIndex)->getCoordinate().second)->upType(BOMB_READY);
	}
	if (passedTime > 1500) {
		currentMap->getBomb(checkIndex)->changeState(currentMap->getBomb(checkIndex)->getState() + 1);
		currentMap->getBomb(checkIndex)->setTime();
	}
	if (currentMap->getBomb(checkIndex)->getState() > 1) {
		currentMap->getBlock(currentMap->getBomb(checkIndex)->getCoordinate().first, currentMap->getBomb(checkIndex)->getCoordinate().second)->downType();
		std::vector<characterWeapon*> playerWeapon;
		currentMap->getBomb(checkIndex)->getOwner()->getWeapon(playerWeapon);
		int bombDistance = playerWeapon[0]->getDistance();
		explosion(bombDistance, checkIndex, true);
		currentMap->deleteBomb();
		return false;
	}
	return true;
}