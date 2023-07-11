#ifndef MAPP_H_
#define MAPP_H_
#include"block.h"
#include"weapon.h"
#include <fstream>
#include<ctime>
#include<random>

class Map
{
public:
    Map(int mRow = 12, int mColumn = 12) : rowSize(mRow), columnSize(mColumn) {
        blockMap = new Block[rowSize * columnSize];
        for(int i = 0; i < rowSize * columnSize; i++)
            blockMap[i].initial(ROAD);
    }
    ~Map() {}
    Block *getBlock(int x, int y) {
        if (y >= rowSize || x >= columnSize); //will be throw()
        return &blockMap[y * columnSize + x];
    }
    void initial() {
        std::ifstream  fin;
        fin.open ("../bombtest/resources/maps/map.txt" ,std::ios::in);
        for(int i = 0; i < rowSize * columnSize; i++){
            char ch;
            fin >> ch;
            if (ch == '0') blockMap[i].initial(ROAD);
            else if (ch == '1') blockMap[i].initial(BLOCK_CAN_BE_DESTROYED_1);
            else if (ch == '3') blockMap[i].initial(BLOCK_CANNOT_BE_DESTROYED_1);
            else if (ch == ' ' || ch == '\n') i--;
        }
    }




    void setBomb(std::pair<int, int> mCoordinate, Character* player) {
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

private:
    int rowSize;
    int columnSize;
    std::vector<mapWeapon*> mapBomb;
    Block *blockMap;
};


#endif // MAPP_H_
