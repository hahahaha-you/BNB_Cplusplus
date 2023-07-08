#ifndef MAPP_H_
#define MAPP_H_
#include"block.h"
#include"weapon.h"

class map
{
public:
    map(int mRow, int mColumn, std::vector<character*> mPlayer) : rowSize(mRow), columnSize(mColumn), player(mPlayer) {
        mapBomb = nullptr;
        blockMap = new block[rowSize * columnSize];
    }
    ~map() {}
    block getBlock(int x, int y) {
        if (x >= rowSize || y >= columnSize); //will be throw()
        return blockMap[x * columnSize + y];
    }
    void initial() {

    }
    void setBomb(std::pair<int, int> mCoordinate, character* player) {
        mapBomb = new mapWeapon(mCoordinate, player);
        mapBomb->setTime();
    }
    void deleteBomb() {
        delete mapBomb;
        mapBomb = nullptr;
    }
    inline mapWeapon* getBomb() { return mapBomb; }
    inline int getRowSize() { return rowSize; }
    inline int getColumnSize() { return columnSize; }

private:
    int rowSize;
    int columnSize;
    mapWeapon* mapBomb;
    block* blockMap;
    std::vector<character*> player;
};


#endif // MAPP_H_