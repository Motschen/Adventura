#pragma once
class Pos {
protected:
    int x;
    int y;
public:
    Pos(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    bool isNegative() {
        return x < 0 || y < 0;
    }
    Pos operator+(Pos offset) {
        return Pos(this->getX() + offset.getX(), this->getY() + offset.getY());
    }
    Pos operator-(Pos offset) {
        return Pos(this->getX() - offset.getX(), this->getY() - offset.getY());
    }
};