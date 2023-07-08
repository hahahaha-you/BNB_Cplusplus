#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include<iostream>
#include<utility>
#include<vector>
#include"weapon.h"

using namespace std;
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
class character{
public:
    ~character(){}
    character(pair<int,int> tCoordinate, double tSpeed) : coordinate(tCoordinate), speed(tSpeed) {
        lives = 1;
        playerDirection = DOWN;
        playerOperation = INVALID_OPERATION;
        characterWeapon* bomb = new characterWeapon("bomb");
        playerWeapon.push_back(bomb);
    }
    void move (double dx, double dy){
        coordinate.first += dx;
        coordinate.second += dy;
    }

    inline double getSpeed() { return speed; }

    inline void addSpeed() { speed += 0.01; }

    inline Operation getOperation() { return playerOperation; }

    inline Direction getDirection() { return playerDirection; }

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
    pair<int,int> coordinate;
    double speed;
    Direction playerDirection;
    Operation playerOperation;
    vector <characterWeapon*> playerWeapon;
    int lives;
};

#endif // CHARACTER_H_