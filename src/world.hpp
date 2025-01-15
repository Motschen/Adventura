#pragma once
#include <vector>
#include <array>
#include "fileutils.hpp"
#include "block.hpp"
#include "blockRegistry.hpp"
#include "blockPos.hpp"

using std::vector;

class World {
public:
    World(BlockRegistry blockRegistry) {
        this->blockRegistry = blockRegistry;
    }
    
    void loadFromFile(string fileLocation) {
        field = {};
        vector<string> file = readFileAsVector(fileLocation);
        
        for (unsigned int y = 0; y < file.size(); y++) {
            for (unsigned int x = 0; x < file.at(y).size(); x++) {
                setBlockAt(BlockPos(x, y), blockRegistry.getByEncoding(file.at(y).at(x)));
                if (file.at(y).at(x) == '|') startPos = BlockPos(x, y);
                if (x > maxX) maxX = x;
            }
            if (y > maxY) maxY = y;
        }
    }
    void setBlockAt(BlockPos pos, Block block) {
        if (pos.isNegative()) return;
        while (field.size() <= pos.getUnsignedY()) field.push_back({});
        while (field[pos.getUnsignedY()].size() <= pos.getUnsignedX()) field[pos.getUnsignedY()].push_back(blockRegistry.AIR);

        field[pos.getUnsignedY()][pos.getX()] = block;
    }

    Block& getBlockAt(BlockPos pos) {
        if (pos.getUnsignedY() < field.size() && pos.getUnsignedX() < field[pos.getUnsignedY()].size()) {
            return field[pos.getY()][pos.getX()];
        }
        //cout << "Out of bounds: " << pos.getX() << ", " << pos.getY() << endl;
        return blockRegistry.AIR;
    }
    bool containsPos(BlockPos pos) {
        return !pos.isNegative() && pos.getUnsignedY() < field.size();
    }
    vector<vector<Block>> getFieldState() {
        return field;
    }
    BlockRegistry getBlockRegistry() {
        return blockRegistry;
    }
    unsigned int getMaxX() {
        return maxX;
    }
    unsigned int getMaxY() {
        return maxY;
    }
    BlockPos getStartPos() {
        return startPos;
    }
private:
    BlockRegistry blockRegistry;
    vector<vector<Block>> field;
    unsigned int maxX = 0;
    unsigned int maxY = 0;
    BlockPos startPos = BlockPos(0, 0);
};