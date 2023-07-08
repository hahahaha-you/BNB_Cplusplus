#ifndef BLOCK_H
#define BLOCK_H
#include<utility>

#define road 0 canbedestroyeda/b

class block
{
public:
    block(std::pair<int,int> bCoordinate,bool bIsRoad,bool bCanBeDestroyed):coordinate(bCoordinate),isRoad(bIsRoad),canBeDestroyed(bCanBeDestroyed){}
    ~block(){}
    void destory(){
        if(canBeDestroyed) isRoad=true;
    }
    bool go(){
        return isRoad;
    }
private:
	int type;
    std::pair<int,int> coordinate;
	bool isRoad=true;
	bool canBeDestroyed=true;
};


#endif // BLOCK_H
