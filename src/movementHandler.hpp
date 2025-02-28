#pragma once
#include <array>

#include "player.hpp"
#include "world.hpp"
#include "blockRegistry.hpp"
#include "output.hpp"

static void tryPushBlock(BlockPos& blockPos, World& world, bool left);
static void tryBlockGravity(BlockPos& blockPos, World& world);

/**
 * Checks if a given value is in a parameter pack of values.
 *
 * This is a C++17 implementation of a function that checks if a given value
 * is in a parameter pack of values. This is useful for checking if a value is
 * in a list of values without having to write a bunch of repetitive code.
 * Source: https://stackoverflow.com/a/15181949
 *
 * @param first The value to search for.
 * @param t The parameter pack of values to search in.
 * @return true if the value is found in the parameter pack, false otherwise.
 */
template<typename First, typename ... T>
static bool is_in(First &&first, T && ... t) {
    return ((first == t) || ...);
}

/**
 * Waits until the user enters a valid key.
 * Used to prompt the user to press any key to continue.
 */
static void waitForInput() {
    char lastChar = ' ';
    while (!is_in(lastChar, 'w', 'a', 's', 'd')) cin >> lastChar;
}

/**
 * Attempts to move the player one block to the left or right.
 *
 * Checks if the neighbour block to the player's feet is not a solid block and
 * if so, moves the player there. In case that block solid and the block above it
 * is not solid, moves the player on top of that block.
 * Otherwise, returns false.
 *
 * @param world Reference to the World object representing the game's world.
 * @param player Reference to the Player object representing the player's state.
 * @param left Whether to move left (true) or right (false).
 * @return true if the player's position was successfully updated, false otherwise.
 */
static bool tryWalk(World& world, Player& player, bool left) {
    BlockPos playerPos = player.getPos();
    BlockPos neighbourPosTorso = playerPos+(left ? BlockPos(-1, 0) : BlockPos(1, 0));
    BlockPos neighbourPosFeet = playerPos+(left ? BlockPos(-1, 1) : BlockPos(1, 1));
    tryPushBlock(neighbourPosFeet, world, left);
    if (!world.getBlockAt(neighbourPosFeet).getSettings().hasCollision()) {
        player.setPos(neighbourPosTorso);
        tryBlockGravity(playerPos, world);
        return true;
    }
    else if (world.getBlockAt(neighbourPosFeet).getSettings().hasCollision() && !world.getBlockAt(neighbourPosTorso).getSettings().isSolid()) {
        left ? player.move(-1, -1) : player.move(1, -1);
        return true;
    }
    return false;
}

/**
 * Attempts to move the player one block downwards.
 *
 * Checks if the block above the player's torso or the block above the player's feet is
 * climbable from the top and if so, moves the player there.
 * Otherwise, returns false.
 *
 * @param world Reference to the World object representing the game's world.
 * @param player Reference to the Player object representing the player's state.
 * @return true if the player's position was successfully updated, false otherwise.
 */
static bool tryGoDown(World& world, Player& player) {
    if (world.getBlockAt(player.getPos()+BlockPos(0, 2)).getSettings().isClimbableFromTop() || world.getBlockAt(player.getPos()+BlockPos(0, 3)).getSettings().isClimbableFromTop()) {
        player.move(0, 1);
        return true;
    }
    return false;
}

/**
 * Attempts to move the player one block upwards.
 *
 * Checks if the block above the player's torso or the block above the player's head is
 * climbable from the bottom and if so, moves the player there.
 * Otherwise, returns false.
 *
 * @param world Reference to the World object representing the game's world.
 * @param player Reference to the Player object representing the player's state.
 * @return true if the player's position was successfully updated, false otherwise.
 */
static bool tryGoUp(World& world, Player& player) {
    if (world.getBlockAt(player.getPos()+BlockPos(0, 1)).getSettings().isClimbableFromBottom() || world.getBlockAt(player.getPos()+BlockPos(0, 2)).getSettings().isClimbableFromBottom()) {
        player.move(0, -1);
        return true;
    }
    return false;
}

/**
 * Attempts to push the block at the given position to the left or right.
 *
 * Checks if the block at the given position is pushable and if so, tries to push it
 * to the left or right by swapping it with the block to its left/right.
 * If the block to the left/right is also pushable, this function will be called
 * recursively to handle the furthest block first.
 *
 * @param blockPos The position of the block to try to push.
 * @param world Reference to the World object representing the current world.
 * @param left Whether to push the block to the left (true) or right (false).
 */
static void tryPushBlock(BlockPos& blockPos, World& world, bool left) {
    BlockPos neighbourBlockPos = blockPos+(left ? BlockPos(-1, 0) : BlockPos(1, 0));
    if (world.getBlockAt(blockPos).getSettings().isPushable()) { 
        if (world.getBlockAt(neighbourBlockPos).getSettings().isPushable()) {
            tryPushBlock(neighbourBlockPos, world, left); // If multiple boxes are next to each other, handle the furthest one first
        }
        if (world.getBlockAt(neighbourBlockPos) == world.getBlockRegistry().AIR) { // Push the box by swapping the blocks
            world.setBlockAt(neighbourBlockPos, world.getBlockAt(blockPos));
            world.setBlockAt(blockPos, world.getBlockRegistry().AIR);
        }
    }
}

/**
 * Checks if the block below the player's feet has gravity and if so,
 * moves it down one block if possible.
 *
 * @param playerPos The position of the player.
 * @param world Reference to the World object representing the current world.
 */
static void tryBlockGravity(BlockPos& playerPos, World& world) {
    if (world.getBlockAt(playerPos.add(0, 2)).getSettings().hasGravity() && world.getBlockAt(playerPos.add(0, 3)) == world.getBlockRegistry().AIR) {
        world.setBlockAt(playerPos.add(0, 3), world.getBlockAt(playerPos.add(0, 2)));
        world.setBlockAt(playerPos.add(0, 2), world.getBlockRegistry().AIR);
    }
}

/**
 * Processes the player's input and attempts to move the player in the game world
 * based on the input character. Supports moving up, left, down, or right
 * using the keys 'w', 'a', 's', 'd' as well as their upper-case equivalents (useful in case caps lock is pressed by accident).
 *
 * @param lastChar The character input representing the player's movement command.
 * @param world Reference to the World object representing the game's world.
 * @param player Reference to the Player object representing the player's state.
 * @return true if the player's position was successfully updated, false otherwise.
 */

static bool onInput(char lastChar, World& world, Player& player) {
    switch (lastChar) {
        case ' ':
        case 'w':
        case 'W':
            return tryGoUp(world, player);

        case 'a':
        case 'A':
            return tryWalk(world, player, true);

        case 's':
        case 'S':
            return tryGoDown(world, player);

        case 'd':
        case 'D':
            return tryWalk(world, player, false);
        
        default: return false;
    }
}

/**
 * Listens for the player's input and updates the game state accordingly.
 * If test mode is enabled, reads input from the file TEST.txt instead of the console.
 * In this case, the game state is updated every 100 milliseconds (to simulate the player's input).
 * If the player dies or reaches the goal, exit the loop.
 */
static void inputLoop(Player& player, World& world, bool testMode, unsigned int worldIndex) {
    vector<string> testFile = readFileAsVector("TEST.txt");
    unsigned int inputIndex = 0;
    while (player.isAlive() && !player.hasReachedGoal()) {
        string currentInput;
        if (testMode) {
            currentInput = testFile[worldIndex][inputIndex];
            inputIndex++;
            if (inputIndex > testFile[worldIndex].length()) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        else cin >> currentInput;
        if (!testMode) {
            jumpBackOneLine();
        }

        for (char lastChar : currentInput) {
            if (onInput(lastChar, world, player))
                redraw(world, player.mapToWorldspace());
        }
    }
    inputIndex = 0;
}
