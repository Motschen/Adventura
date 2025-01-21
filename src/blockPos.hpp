#pragma once
class BlockPos {
    int x;
    int y;
public:
    BlockPos(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    unsigned int getUnsignedX() {
        return static_cast<unsigned int>(x);
    }
    unsigned int getUnsignedY() {
        return static_cast<unsigned int>(y);
    }
    bool isNegative() {
        return x < 0 || y < 0;
    }
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