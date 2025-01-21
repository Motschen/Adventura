#include "player.hpp"
#include "world.hpp"
#include "blockRegistry.hpp"

bool tryWalk(World& world, Player& player, bool left);
bool tryGoDown(World& world, Player& player);
bool tryGoUp(World& world, Player& player);
bool tryPushBlock(BlockPos& blockPos, World& world, bool left);

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

bool onInput(char lastChar, World& world, Player& player) {
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
bool tryWalk(World& world, Player& player, bool left) {
    BlockPos neighbourPosTorso = player.getPos()+(left ? BlockPos(-1, 0) : BlockPos(1, 0));
    BlockPos neighbourPosFeet = player.getPos()+(left ? BlockPos(-1, 1) : BlockPos(1, 1));
    tryPushBlock(neighbourPosFeet, world, left);
    if (!world.getBlockAt(neighbourPosFeet).getSettings().hasCollision()) {
        player.setPos(neighbourPosTorso);
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
bool tryGoDown(World& world, Player& player) {
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
bool tryGoUp(World& world, Player& player) {
    if (world.getBlockAt(player.getPos()+BlockPos(0, 1)).getSettings().isClimbableFromBottom() || world.getBlockAt(player.getPos()+BlockPos(0, 2)).getSettings().isClimbableFromBottom()) {
        player.move(0, -1);
        return true;
    }
    return false;
}
bool tryPushBlock(BlockPos& blockPos, World& world, bool left) {
    BlockPos neighbourBlockPos = blockPos+(left ? BlockPos(-1, 0) : BlockPos(1, 0));
    if (world.getBlockAt(blockPos).getSettings().isPushable()) { 
        if (world.getBlockAt(neighbourBlockPos).getSettings().isPushable()) {
            tryPushBlock(neighbourBlockPos, world, left);
        }
        if (world.getBlockAt(neighbourBlockPos) == world.getBlockRegistry().AIR) {
            world.setBlockAt(neighbourBlockPos, world.getBlockAt(blockPos));
            world.setBlockAt(blockPos, world.getBlockRegistry().AIR);
            return true;
        }
    }
    return false;
}