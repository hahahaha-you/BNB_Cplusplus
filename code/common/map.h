#ifndef MAPP_H_
#define MAPP_H_
#include"block.h"
#include"character.h"

class map
{
public:
    map(int mRow, int mColumn, std::vector<character*> mPlayer) : rowSize(mRow), columnSize(mColumn), player(mPlayer) {
        mapBomb = nullptr;
        blockMap = new block[rowSize * columnSize];
    }
    ~map() {}
    Block* getBlock(int x, int y) {
        if (x >= rowSize || y >= columnSize) throw();
        return blockMap[x * columnSize + y];
    }
    void initial() {

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
    block* blockMap;
    std::vector<character*> player;
};


#endif // MAPP_H_