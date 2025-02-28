#pragma once
class BlockPos {
    int x;
    int y;
public:
    /**
     * Define an in-world position.
     * 
     * @param xCoord The x-coordinate of the BlockPos.
     * @param yCoord The y-coordinate of the BlockPos.
     */
    BlockPos(int xCoord, int yCoord) {
        this->x = xCoord;
        this->y = yCoord;
    }
    /**
     * Define an in-world position.
     * 
     * @param xCoord The x-coordinate of the BlockPos.
     * @param yCoord The y-coordinate of the BlockPos.
     */
    BlockPos(unsigned int xCoord, unsigned int yCoord) {
        this->x = static_cast<int>(xCoord);
        this->y = static_cast<int>(yCoord);
    }
    
    /**
     * @return The x-coordinate of the BlockPos.
     */
    int getX() {
        return x;
    }

    /**
     * @return The y-coordinate of the BlockPos.
     */
    int getY() {
        return y;
    }

    /**
     * @return The x-coordinate of the BlockPos as an unsigned integer.
     * @pre x >= 0
     */
    unsigned int getUnsignedX() {
        return static_cast<unsigned int>(x);
    }

    /**
     * @return The y-coordinate of the BlockPos as an unsigned integer.
     * @pre y >= 0
     */
    unsigned int getUnsignedY() {
        return static_cast<unsigned int>(y);
    }
    
    /**
     * @return True if the BlockPos is negative, false otherwise.
     * 
     * A BlockPos is considered negative if either the x-coordinate or the y-coordinate is negative.
     */
    bool isNegative() {
        return x < 0 || y < 0;
    }

    /**
     * Add the given coordinates to the BlockPos.
     * 
     * @param xOffset The x-coordinate to add.
     * @param yOffset The y-coordinate to add.
     * @return The BlockPos with the given coordinates added.
     */
    BlockPos add(int xOffset, int yOffset) {
        return BlockPos(this->x + xOffset, this->y + yOffset);
    }
    
    BlockPos operator+(BlockPos offset) {
        return BlockPos(this->getX() + offset.getX(), this->getY() + offset.getY());
    }
    BlockPos operator-(BlockPos offset) {
        return BlockPos(this->getX() - offset.getX(), this->getY() - offset.getY());
    }
};
