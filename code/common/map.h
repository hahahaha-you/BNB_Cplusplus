#ifndef MAPP_H_
#define MAPP_H_
#include"block.h"
#include"weapon.h"

class map
{
public:
    map(int mRow, int mColumn, std::vector<character*> mPlayer) : rowSize(mRow), columnSize(mColumn), player(mPlayer) {
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
        mapWeapon* newMapBomb = new mapWeapon(mCoordinate, player);
        newMapBomb->setTime();
        mapBomb.push_back(newMapBomb);
    }
    void deleteBomb() {
        mapBomb.erase(mapBomb.begin() + 1);
    }
    inline mapWeapon* getBomb(int index) { 
        if (index >= mapBomb.size()) return nullptr;
        return mapBomb[index];
    }
    inline int getRowSize() { return rowSize; }
    inline int getColumnSize() { return columnSize; }

private:
    int rowSize;
    int columnSize;
    std::vector<mapWeapon*>mapBomb;
    block* blockMap;
    std::vector<character*> player;
};


#endif // MAPP_H_