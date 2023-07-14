#ifndef WEAPON_H_
#define WEAPON_H_
#include<string>
#include<time.h>
#include"character.h"


class mapWeapon
{
public:
    mapWeapon(std::pair<int, int> mCoordinate, Character* player) : coordinate(mCoordinate), owner(player) {
        state = 0;
        owner->setLastBombCoordinate();
    }
    inline Character* getOwner() { return owner; }
    inline void setTime () { startTime = clock(); }
    inline clock_t getTime() { return startTime; }
    inline void changeState(int nextState) { state = nextState; }
    inline int getState() { return state; }
    inline std::pair<int, int> getCoordinate() { return coordinate; }
private:
    Character* owner;
    std::pair<int, int> coordinate;
    clock_t startTime;
    int state;
};
#endif // WEAPON_H_
