#pragma once
class BlockPos {
    int x;
    int y;
public:
    /**
     * Define an in-world position.
     * 
     * @param x The x-coordinate of the BlockPos.
     * @param y The y-coordinate of the BlockPos.
     */
    BlockPos(int x, int y) {
        this->x = x;
        this->y = y;
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
     * @param x The x-coordinate to add.
     * @param y The y-coordinate to add.
     * @return The BlockPos with the given coordinates added.
     */
    BlockPos add(int x, int y) {
        return BlockPos(this->x + x, this->y + y);
    }
    
    BlockPos operator+(BlockPos offset) {
        return BlockPos(this->getX() + offset.getX(), this->getY() + offset.getY());
    }
    BlockPos operator-(BlockPos offset) {
        return BlockPos(this->getX() - offset.getX(), this->getY() - offset.getY());
    }
};