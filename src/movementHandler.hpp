#include "player.hpp"
#include "world.hpp"
#include "blockRegistry.hpp"

bool tryGoDown(World& world, Player& player);
bool tryGoUp(World& world, Player& player);

bool onInput(char lastChar, World& world, Player& player) {
    switch (lastChar) {
        case 'w':
        case 'W':
            return tryGoUp(world, player);

        case 'a':
        case 'A':
            player.move(-1, 0);
            return true;

        case 's':
        case 'S':
            return tryGoDown(world, player);

        case 'd':
        case 'D':
            player.move(1, 0);
            return true;
        
        default: return false;
    }
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
    return false;
}