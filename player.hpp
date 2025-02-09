#pragma once
#include <array>
#include <thread>
#include <chrono>

#include "blockPos.hpp"
#include "output.hpp"

class Player {
public:
    /**
     * Initializes a new Player at the specified starting position in the provided world.
     *
     * @param initialPos The initial position of the player within the world.
     * @param currentWorld A reference to the World object representing the game world.
     */
    Player(BlockPos initialPos, World& currentWorld) : world(currentWorld) {
        this->pos = initialPos;
        this->world = currentWorld;
        playerTexture = REGULAR_PLAYER_TEXTURE;
    }
    
    /*initialP
     * Retrieves the current position of the player in the world.
     *
     * @return The current BlockPos representing the player's position.
     */
    BlockPos getPos() {
        return pos;
    }

    /**
     * Move the player by the specified x and y offsets.
     *
     * @param x The x offset to move by.
     * @param y The y offset to move by.
     */
    void move(int x, int y) {
        move(BlockPos(x, y));
    }

    /**
     * Move the player by the specified BlockPos offset.
     *
     * @param offset The BlockPos representing the offset to move the player by.
     */
    void move(BlockPos offset) {
        setPos(pos + offset);
    }

    
    /**
     * Updates the player's position and checks for any conditions that would update the state of the player.
     * 
     * @param newPos The position to move the player to.
     */
    void setPos(BlockPos newPos) {
        if (!world.containsPos(newPos)) {
            alive = false;
            return;
        }
        this->pos = newPos;

        if (world.getBlockAt(newPos) == world.getBlockRegistry().GOAL) reachedGoal = true;

        if (world.getBlockAt(newPos.add(0, 2)) == world.getBlockRegistry().WATER) fallLength = 0;

        isFreeFalling = !world.getBlockAt(newPos.add(0, 2)).getSettings().isSolid();
        if (isFreeFalling) {
            fallLength += 1;
            if (fallLength > 2) playerTexture = FALLING_PLAYER_TEXTURE;
            redraw(world, this->mapToWorldspace());
            std::this_thread::sleep_for(std::chrono::milliseconds(100 / fallLength + 50));
            move(0, 1);
        }
        else {
            playerTexture = REGULAR_PLAYER_TEXTURE;
            if (fallLength > 5) unalive();
            fallLength = 0;
        }

        if (world.getBlockAt(newPos.add(0, 2)).getSettings().isLethal()) unalive();
    }

    /**
     * Handle the unfortunate case of a player dying :(
     */
    void unalive() {
        playerTexture = DEAD_PLAYER_TEXTURE;
        redraw(world, this->mapToWorldspace());
        alive = false;
    }
    
    /**
     * Checks if the player is still alive.
     *
     * @return true if the player is alive, false otherwise.
     */
    bool isAlive() {
        return alive;
    }
    
    /**
     * Checks if the player has reached the goal in the current world.
     *
     * @return true if the player has reached the goal, false otherwise.
     */
    bool hasReachedGoal() {
        return reachedGoal;
    }
    
    /**
     * Maps the player texture to the player's position in the current game world.
     * 
     * @return A 2D vector of characters representing the player's position in the world.
     */
    vector<vector<char>> mapToWorldspace() {
        vector<vector<char>> map;
        for (unsigned int y = 0; y <= world.getMaxY(); y++) {
            for (unsigned int x = 0; x <= world.getMaxX(); x++) {
                while (map.size() <= y) map.push_back({});
                while (map[y].size() <= x) map[y].push_back(' ');

                int yOffset = static_cast<int>(y)-static_cast<int>(pos.getUnsignedY()) + 1;
                int xOffset = static_cast<int>(x)-static_cast<int>(pos.getUnsignedX()) + 1;

                char encoding = ' ';
                if (yOffset >= 0 && yOffset < (static_cast<int>(static_cast<size_t>(playerTexture.size()))) && 
                xOffset >= 0 && xOffset < (static_cast<int>(playerTexture.at(static_cast<size_t>(yOffset)).size()))) {
                    encoding = playerTexture.at(static_cast<unsigned int>(yOffset)).at(static_cast<unsigned int>(xOffset));
                }
                    
                map[y][x] = encoding;
            }
        }
        return map;
    }

private:
    World& world;
    std::array<std::array<char, 3>, 3> playerTexture;
    BlockPos pos = BlockPos(0, 0);
    bool alive = true;
    bool isFreeFalling = false;
    bool reachedGoal = false;
    int fallLength = 0;

    const std::array<std::array<char, 3>, 3> REGULAR_PLAYER_TEXTURE {{
        {' ', 'o', ' '},
        {'/', '|', '\\'},
        {'/', ' ', '\\'}
        // Player pos is at the center '|' char
    }};
    const std::array<std::array<char, 3>, 3> FALLING_PLAYER_TEXTURE {{
        {'\\', 'o', '/'},
        {' ', '|', ' '},
        {'/', ' ', '\\'}
    }};
    const std::array<std::array<char, 3>, 3> DEAD_PLAYER_TEXTURE {{
        {' ', ' ', ' '},
        {'/', '-', 'X'},
        {'/', ' ', '\\'}
    }};
};
