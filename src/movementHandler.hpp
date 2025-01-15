#include "player.hpp"
#include "world.hpp"
#include "blockRegistry.hpp"

bool tryWalk(World& world, Player& player, bool left);
bool tryGoDown(World& world, Player& player);
bool tryGoUp(World& world, Player& player);

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
bool tryWalk(World& world, Player& player, bool left) {
    if (!world.getBlockAt(player.getPos()+(left ? BlockPos(-1, 1) : BlockPos(1, 1))).getSettings().hasCollision()) {
        player.move(left ? BlockPos(-1, 0) : BlockPos(1,0));
        return true;
    }
    return false;
}
bool tryGoDown(World& world, Player& player) {
    if (world.getBlockAt(player.getPos()+BlockPos(0, 2)).getSettings().isClimbableFromTop() || world.getBlockAt(player.getPos()+BlockPos(0, 3)).getSettings().isClimbableFromTop()) {
        player.move(0, 1);
        return true;
    }
    return false;
}
bool tryGoUp(World& world, Player& player) {
    if (world.getBlockAt(player.getPos()+BlockPos(0, 1)).getSettings().isClimbableFromBottom() || world.getBlockAt(player.getPos()+BlockPos(0, 2)).getSettings().isClimbableFromBottom()) {
        player.move(0, -1);
        return true;
    }
    else if (world.getBlockAt(player.getPos()+BlockPos(1, 1)).getSettings().hasCollision() && !world.getBlockAt(player.getPos()+BlockPos(1, 0)).getSettings().isSolid()) {
        player.move(1, -1);
        return true;
    }
    else if (world.getBlockAt(player.getPos()+BlockPos(-1, 1)).getSettings().hasCollision() && !world.getBlockAt(player.getPos()+BlockPos(-1, 0)).getSettings().isSolid()) {
        player.move(-1, -1);
        return true;
    }
    return false;
}