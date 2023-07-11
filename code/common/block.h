#ifndef BLOCK_H
#define BLOCK_H
#include<utility>

enum BlockType {
	ROAD = 0,
	BLOCK_CAN_BE_DESTROYED_1,
	BLOCK_CAN_BE_DESTROYED_2,
	BLOCK_CANNOT_BE_DESTROYED_1,
	BLOCK_CANNOT_BE_DESTROYED_2,
    BOMB_EXPLOSION,
    BOMB_READY
};

class Block
{
public:
    Block() = default;
    ~Block() {}
	void initial(BlockType newType) { type = newType; }
	inline BlockType getType() { return type; }
	bool downType() {
		if (type < 3) {
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
		return false;
	}

private:
	BlockType type;
};


#endif // BLOCK_H
