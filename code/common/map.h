#ifndef MAPP_H_
#define MAPP_H_
#include"block.h"
#include"weapon.h"

class Map
{
public:
    Map(int mRow, int mColumn, std::vector<character*> mPlayer) : rowSize(mRow), columnSize(mColumn), player(mPlayer) {
        blockMap = new block[rowSize * columnSize];
    }
    ~Map() {}
    block *getBlock(int x, int y) {
        if (x >= rowSize || y >= columnSize); //will be throw()
        return &blockMap[x * columnSize + y];
    }
    void initial() {

    }
    void setBomb(std::pair<int, int> mCoordinate, character* player) {
        mapWeapon *newMapBomb = new mapWeapon(mCoordinate, player);
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
    inline int getRowSize() const { return rowSize; }
    inline int getColumnSize() const { return columnSize; }
    std::vector<character *> getPlayers() const { return player; }

private:
    int rowSize;
    int columnSize;
    std::vector<mapWeapon*>mapBomb;
    block *blockMap;
    std::vector<character *> player;
};


#endif // MAPP_H_