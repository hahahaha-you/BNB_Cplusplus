#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include<iostream>
#include<utility>
#include<vector>
#include"weapon.h"

enum Operation {
    TURN_LEFT = 0,
    TURN_RIGHT,
    TURN_UP,
    TURN_DOWN,
    ATTACT,
    INVALID_OPERATION
};
enum Direction {
    LEFT = 0,
    RIGHT,
    UP,
    DOWN
};

class characterWeapon
{
public:
    characterWeapon(std::string wID) :ID(wID) {
        if (ID == "bomb") distance = 1;
    }
    ~characterWeapon() {}
    inline std::string getID() { return ID; }
    inline int getDistance() { return distance; }
    inline void changeDistance() { if (ID == "bomb") distance++; }
private:
    std::string ID;
    int distance;

};

class character{
public:
    ~character(){}
    character(std::pair<double,double> tCoordinate, double tSpeed) : coordinate(tCoordinate), speed(tSpeed) {
        lives = 1;
        playerDirection = DOWN;
        playerOperation = INVALID_OPERATION;
        characterWeapon* bomb = new characterWeapon("bomb");
        playerWeapon.push_back(bomb);
        //-1 records the player is not standing in the same position as the bomb now
        lastBombCoordinate.first = -1;  
    }

    inline void setLastBombCoordinate() { 
        lastBombCoordinate.first  = (int)coordinate.first;
        lastBombCoordinate.second = (int)coordinate.second;
    }

    inline void deleteLastBomb() { lastBombCoordinate.first = -1; }

    inline std:: pair<int, int> getLastBombCoordinate() { return lastBombCoordinate; }

    inline void move(std::pair<double, double> newCoordinate) { coordinate = newCoordinate;}

    inline double getSpeed() { return speed; }

    inline void addSpeed() { speed += 0.01; }

    inline Operation getOperation() { return playerOperation; }

    inline Direction getDirection() { return playerDirection; }

    inline std:: pair<double, double> getCoordinate() { return coordinate; }

    inline void getWeapon(std::vector<characterWeapon*> &currentWeapon) { currentWeapon = playerWeapon; }
    
    void updateOperation (Operation tOperation) {
        playerOperation = tOperation;
        switch (tOperation) {
        case TURN_LEFT:
            playerDirection = LEFT;
            break;
        case TURN_RIGHT:
            playerDirection = RIGHT;
            break;
        case TURN_UP:
            playerDirection = UP;
            break;
        case TURN_DOWN:
            playerDirection = DOWN;
            break;
        default: break;
        }
    }
private:
    std::pair<double, double> coordinate;
    std::pair<int, int> lastBombCoordinate;
    double speed;
    Direction playerDirection;
    Operation playerOperation;
    std::vector <characterWeapon*> playerWeapon;
    int lives;
};

#endif // CHARACTER_H_