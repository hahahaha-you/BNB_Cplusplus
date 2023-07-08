#ifndef MAPP_H_
#define MAPP_H_
#include"block.h"
#include"character.h"
 
class map
{
public:
    map(int mRow,int mColumn, std::vector<character*> mPlayer) : rowSize(mRow), columnSize(mColumn), player(mPlayer) {
        mapBomb = nullptr;
    } 
    ~map(){}
    void initial(){
        
    }
    void setBomb(pair<int, int> mCoordinate) { 
        mapBomb = new mapWeapon(mCoordinate); 
        mapBomb->setTime();
    }
    void deleteBomb() {
        delete mapBomb;
        mapBomb = nullptr;
    }
    mapWeapon* getBomb() { return mapBomb; }

private:
    int rowSize;
    int columnSize;
    mapWeapon* mapBomb;
    std::vector<character*> player;
};


#endif // MAPP_H_