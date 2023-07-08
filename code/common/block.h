#ifndef BLOCK_H
#define BLOCK_H
#include<utility>

enum BlockType {
	ROAD = 0,
	BLOCK_CAN_BE_DESTROYED_1,
	BLOCK_CAN_BE_DESTROYED_2,
	BLOCK_CANNOT_BE_DESTROYED_1,
	BLOCK_CANNOT_BE_DESTROYED_2
};

class block
{
public:
	block() = default;
	block(BlockType bType) : type(bType) {}
	~block() {}
	void initial(BlockType newType) { type = newType; }
	inline BlockType getType() { return type; }
	bool changeType() {
		if (type < 3) {
			type = ROAD;
			return true;
		}
		return false;
	}

private:
	BlockType type;
};


#endif // BLOCK_H
