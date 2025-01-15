#pragma once
#include <array>
#include "blockPos.hpp"

class Player {
public:
    Player(BlockPos pos, World& world) : world(world) {
        this->pos = pos;
        this->world = world;
        playerTexture = {{
            {' ', 'o', ' '},
            {'/', '|', '\\'},
            {'/', ' ', '\\'}
        }};       // Player pos is at the bottom center
    }
    
    BlockPos getPos() {
        return pos;
    }
    void move(int x, int y) {
        move(BlockPos(x, y));
    }
    void move(BlockPos offset) {
        setPos(pos + offset);
    }
    void setPos(BlockPos pos) {
        if (!world.containsPos(pos)) {
            alive = false;
            return;
        }
        this->pos = pos;

        if (world.getBlockAt(pos) == world.getBlockRegistry().GOAL) reachedGoal = true;

        
        isFreeFalling = !world.getBlockAt(pos+BlockPos(0, 2)).getSettings().isSolid();
        if (isFreeFalling) {
            fallLength += 1;
            if (world.getBlockAt(pos+BlockPos(0, 2)) == world.getBlockRegistry().WATER) fallLength = 0;
            move(BlockPos(0, 1));
        }
        else {
            if (fallLength > 5) alive = false;
            fallLength = 0;
        }

        if (world.getBlockAt(pos+BlockPos(0, 2)).getSettings().isLethal()) alive = false;
    }
    bool isAlive() {
        return alive;
    }
    bool hasReachedGoal() {
        return reachedGoal;
    }
    vector<vector<char>> mapToWorldspace() {
        vector<vector<char>> map;
        for (unsigned int y = 0; y <= world.getMaxY(); y++) {
            for (unsigned int x = 0; x <= world.getMaxX(); x++) {
                while (map.size() <= y) map.push_back({});
                while (map[y].size() <= x) map[y].push_back(' ');

                int yOffset = y-pos.getY() + 1;
                int xOffset = x-pos.getX() + 1;

                char encoding = ' ';
                if (yOffset >= 0 && yOffset < static_cast<int>(playerTexture.size()) && 
                xOffset >= 0 && xOffset < static_cast<int>(playerTexture.at(yOffset).size())) {
                    encoding = playerTexture.at(yOffset).at(xOffset);
                }
                    
                map[y][x] = encoding;
            }
        }
        return map;
    }

private:
    World world;
    std::array<std::array<char, 3>, 3> playerTexture;
    BlockPos pos = BlockPos(0, 0);
    bool alive = true;
    bool isFreeFalling = false;
    bool reachedGoal = false;
    int fallLength = 0;
};