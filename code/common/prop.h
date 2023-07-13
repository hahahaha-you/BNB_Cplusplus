#include<utility>
#include"character.h"

#ifndef _PROP_H_
#define _PROP_H_
#include<utility>
#include"character.h"


enum propType{
    LASER

};

class Prop {
private:
    std::pair<int,int> coordinate;
    propType type;
    int ID;
    bool exist;
public:
    Prop(std::pair<int,int> pCoordinate, propType pType, int pID): coordinate(pCoordinate), type(pType), ID(pID), exist(true){}
    ~Prop(){}
    inline std::pair<int,int> getCoordinate() { return coordinate; }
    inline propType getType() { return type; }
    inline int getID() { return ID; }
    inline bool pickUpProp() { 
        if(exist){
            exist = false; 
            return true;
        }
        return false;
    }
    // inline bool propExists() { return exist; }
};

#endif //_PROP_H_