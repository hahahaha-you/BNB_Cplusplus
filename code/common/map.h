#ifndef MAPP_H_
#define MAPP_H_
#include"block.h"
#include"weapon.h"
#include <random>
#include <ctime>

class Map
{
public:
    Map(int mRow = 12, int mColumn = 12) : rowSize(mRow), columnSize(mColumn) {
        blockMap = new Block[rowSize * columnSize];
    }
    ~Map() {}
    Block *getBlock(int x, int y) {
        if (x >= rowSize || y >= columnSize); //will be throw()
        return &blockMap[x * columnSize + y];
    }
        void initial(int destroyableBlockCnt = 12, int undestroyableBlockCnt = 12) {
        // cout<<"initial() ";
        for(int i=0;i<columnSize*rowSize;i++){
            blockMap[i].initial(ROAD);
        }
        for(int i=0;i<undestroyableBlockCnt;i++){
            // cout<<"1";
            // unsigned int seed = time(0);
            // srand(seed);
            // int location = rand() % (columnSize * rowSize);

            std::default_random_engine e;
            e.seed(clock());
            int location = e() % (columnSize * rowSize);
            // cout<<"location="<<location;
            if(blockMap[location].getType() >= BLOCK_CANNOT_BE_DESTROYED_1||location==0||location==1||location==columnSize||location==columnSize*rowSize-1||location==columnSize*rowSize-2||location==columnSize*(rowSize-1)) {
                i--;
                continue;
            }
            // cout<<"4";
            std::vector<Block *> blockGroup;
            // cout<<" "<<location<<"  ";
            if(adjacent(location%columnSize, location/columnSize, blockGroup) == -1){
                // cout<<"a";
                i--;
            }else{
                // cout<<"b";
                blockMap[location].upType(BLOCK_CANNOT_BE_DESTROYED_1);
                // cout<<location<<" "<<blockMap[location].getType()<<"      ";
            }
            // cout<<"c";
        }
        // cout<<"D"<<endl;
        // for(int i=0;i<columnSize*rowSize;i++){
        //     if(i%columnSize==0)cout<<endl;
        //     if(blockMap[i].getType()==ROAD){
        //         cout<<"+";
        //     }else{
        //         cout<<"&";
        //     }
        // }
        for(int i=0;i<destroyableBlockCnt;i++){
            std::default_random_engine e;
            e.seed(clock());
            int location = e() % (columnSize * rowSize);
            if(blockMap[location].getType() != ROAD||location==0||location==1||location==columnSize||location==columnSize*rowSize-1||location==columnSize*rowSize-2||location==columnSize*(rowSize-1)) {
                i--;
                continue;
            }
            blockMap[location].upType(BLOCK_CAN_BE_DESTROYED_1);

        }
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
    int adjacent(int x, int y, std::vector<Block *> & blockGroup) {
        // cout<<"adj"<<x<<" "<<y<<endl;
        int cnt=0;
        // cout<<"x";
        Block *thisBlock=getBlock(x,y);
        // cout<<"y";
        if(thisBlock == NULL || (thisBlock->getType() < 3 && blockGroup.size()!=0)) {
            // cout<<"return0";
            return 0;
        }
        for(int i=0;i<blockGroup.size();i++) {
            // cout;
            if(blockGroup[i]==thisBlock) return 0;
        }
        blockGroup.push_back(thisBlock);
        cnt++;
        int a=adjacent(x, y-1, blockGroup);
        if( a<0 || cnt+a>=4 )return -1;
        cnt+=a;
        a=adjacent(x, y+1, blockGroup);
        if( a<0 || cnt+a>=4 )return -1;
        cnt+=a;
        a=adjacent(x-1, y, blockGroup);
        if( a<0 || cnt+a>=4 )return -1;
        cnt+=a;
        a=adjacent(x+1, y, blockGroup);
        if( a<0 || cnt+a>=4 )return -1;
        cnt+=a;
        // cout<<"cnt"<<cnt;
        return cnt;
    }

private:
    int rowSize;
    int columnSize;
    std::vector<mapWeapon*>mapBomb;
    Block *blockMap;
};


#endif // MAPP_H_