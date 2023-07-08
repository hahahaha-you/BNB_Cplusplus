#ifndef WEAPON_H_
#define WEAPON_H_
#include<string>
#include<time.h>

class characterWeapon
{
public:
    characterWeapon(std::string wID):ID(wID){
        if (ID == "bomb") distance = 1;
    }
    ~characterWeapon() {}
    inline std::string getID() { return ID; }
    inline int getDistance(){ return distance; }
    inline void changeDistance () { if (ID == "bomb") distance++; }
private:
    std::string ID;
    int distance;
    
};

class mapWeapon
{
public:
    mapWeapon(pair<int,int> mCoordinate, character* player) : coordinate(mCoordinate), owner(player) {
        state = 0;
    }
    inline character* getOwner() { return owner; }
    inline void setTime () { startTime = time(NULL); }
    inline time_t getTime() { return startTime; }
    inline void changeState(int nextState) { state = nextState; }
    inline int getState() { return state; }
private:
    character* owner;
    pair<int, int> coordinate;
    time_t startTime;
    int state;
};
#endif // WEAPON_H_