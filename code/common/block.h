#ifndef BLOCK_H
#define BLOCK_H
#include<utility>

enum BlockType {
    ROAD = 0,
    BLOCK_CAN_BE_DESTROYED_1,
    BLOCK_CAN_BE_DESTROYED_2,
    BLOCK_CANNOT_BE_DESTROYED_1,
    BLOCK_CANNOT_BE_DESTROYED_2,
    BOMB_READY,
    BOMB_EXPLOSION_LEFT,
    BOMB_EXPLOSION_RIGHT,
    BOMB_EXPLOSION_UP,
    BOMB_EXPLOSION_DOWN,
    BOMB_EXPLOSION_CENTRAL,
    LASER_EXPLOSION_LEFT,
    LASER_EXPLOSION_RIGHT,
    LASER_EXPLOSION_UP,
    LASER_EXPLOSION_DOWN,
    LASER_EXPLOSION_CENTRAL_LEFT,
    LASER_EXPLOSION_CENTRAL_RIGHT,
    LASER_EXPLOSION_CENTRAL_UP,
    LASER_EXPLOSION_CENTRAL_DOWN
};

class Block
{
public:
    Block() = default;
    ~Block() {}
    void initial(BlockType newType) { type = newType; }
    inline BlockType getType() { return type; }
    bool downType() {
        if (type < 3 || type > 4) {
            type = ROAD;
            return true;
        }
        return false;
    }

    bool upType(BlockType nextType) {
        if (type == ROAD) {
            type = nextType;
            return true;
        }
        if (type == BOMB_READY && nextType == BOMB_EXPLOSION_CENTRAL){
            type = nextType;
            return true;
        }
        return false;
    }

    bool explodeType(BlockType nextType) {
        if ((type < BLOCK_CANNOT_BE_DESTROYED_1 || type > BLOCK_CANNOT_BE_DESTROYED_2) && type != BOMB_READY){
            type = nextType;
            return true;
        }
        return false;
    }

    bool recoverType() {
        if(type >= LASER_EXPLOSION_LEFT && type <= LASER_EXPLOSION_CENTRAL_DOWN){
            type = ROAD;
            return true;
        }
        return false;
    }

private:
    BlockType type;
};


#endif // BLOCK_H