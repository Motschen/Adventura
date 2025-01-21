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
    /**
     * Create a World object using the blocks defined in BlockRegistry.
     * 
     * @param blockRegistry The BlockRegistry to use.
     */
    World(BlockRegistry blockRegistry) {
        this->blockRegistry = blockRegistry;
    }
    
    /**
     * Load the world from the given text file.
     * - The character '|' is the player's starting position.
     * - The characters in the file are mapped to the corresponding blocks in the block registry.
     * - All other characters are kept as purely visual decoration blocks.
     * 
     * @param fileLocation The location of the file to load.
     */
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
    /**
     * Sets the block at the given position in the world.
     * 
     * In case the position is outside the current bounds of the world, the world will be automatically be expanded.
     * If the position is negative, an error will be logged.
     * 
     * @param pos The position to set the block at.
     * @param block The block to set at that position.
     */
    void setBlockAt(BlockPos pos, Block block) {
        if (pos.isNegative()) cout << "Tried to set block at negative position: (x: " << pos.getX() << ", y:" << pos.getY() << ")" << endl;
        while (field.size() <= pos.getUnsignedY()) field.push_back({});
        while (field[pos.getUnsignedY()].size() <= pos.getUnsignedX()) field[pos.getUnsignedY()].push_back(blockRegistry.AIR);

        field[pos.getUnsignedY()][pos.getX()] = block;
        if (block.getSettings().hasGravity() && containsPos(pos.add(0, 1)) && getBlockAt(pos.add(0, 1)) == blockRegistry.AIR) {
            setBlockAt(pos.add(0, 1), block);
            setBlockAt(pos, blockRegistry.AIR);
        }
    }

    /**
     * Get the block at the given position in the world.
     * 
     * In position is outside the current bounds of the world, the AIR block will be returned.
     * 
     * @param pos The position to get the block at.
     * @return The block at that position.
     */
    Block& getBlockAt(BlockPos pos) {
        if (pos.getUnsignedY() < field.size() && pos.getUnsignedX() < field[pos.getUnsignedY()].size()) {
            return field[pos.getY()][pos.getX()];
        }
        //cout << "Out of bounds: " << pos.getX() << ", " << pos.getY() << endl;
        return blockRegistry.AIR;
    }

    /**
     * Checks whether the given position is within the bounds of the world, or not.
     * 
     * @param pos The position to check.
     * @return True if the position is non-negative and within the current bounds of the world, false otherwise.
     */
    bool containsPos(BlockPos pos) {
        return !pos.isNegative() && pos.getUnsignedY() < field.size();
    }
    
    /**
     * @return The current state of the world as a 2D vector of blocks.
     */
    vector<vector<Block>> getFieldState() {
        return field;
    }

    /**
     * Get the block registry for the world.
     * 
     * @return The block registry containing all registered blocks.
     */
    BlockRegistry getBlockRegistry() {
        return blockRegistry;
    }
    
    /**
     * Get the biggest X (horizontal) value in the world.
     * 
     * @return The maximum X value.
     */
    unsigned int getMaxX() {
        return maxX;
    }

    /**
     * Get the biggest Y (vertical) value in the world.
     * 
     * @return The maximum Y value.
     */
    unsigned int getMaxY() {
        return maxY;
    }
    
    /**
     * Get the starting position of the player in the world.
     * 
     * @return The BlockPos representing the starting position in the current level.
     */

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