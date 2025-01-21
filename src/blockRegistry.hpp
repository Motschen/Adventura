#pragma once
#include <vector>
#include <string>
#include "block.hpp"

using std::vector;
using std::string;

class BlockRegistry {
public:
    Block AIR = Block(Identifier("adventura", "air"), ' ', BlockSettingsBuilder().nonSolid().build());
    Block WATER = Block(Identifier("adventura", "water"), '~', Color::BRIGHT_BLUE, BlockSettingsBuilder().nonSolid().build());
    Block PLATFORM = Block(Identifier("adventura", "platform"), '-', BlockSettingsBuilder().build());
    Block LADDER = Block(Identifier("adventura", "ladder"), 'H', Color::BRIGHT_MAGENTA, BlockSettingsBuilder().climbableFromBottom().climbableFromTop().build());
    Block START = Block(Identifier("adventura", "start"), 'S', BlockSettingsBuilder().nonSolid().build());
    Block GOAL = Block(Identifier("adventura", "goal"), 'O', Color::BRIGHT_GREEN, BlockSettingsBuilder().nonSolid().build());
    Block WALL = Block(Identifier("adventura", "wall"), '0', Color::BRIGHT_BLACK, BlockSettingsBuilder().collidable().build());
    Block SPIKE = Block(Identifier("adventura", "spike"), '^', Color::BRIGHT_RED, BlockSettingsBuilder().lethal().build());
    Block BOX = Block(Identifier("adventura", "box"), 'x', Color::BRIGHT_CYAN, BlockSettingsBuilder().pushable().collidable().gravity().build());

    BlockRegistry() {
        registerBlock(AIR);
        registerBlock(WATER);
        registerBlock(PLATFORM);
        registerBlock(LADDER);
        registerBlock(START);
        registerBlock(GOAL);
        registerBlock(WALL);
        registerBlock(SPIKE);
        registerBlock(BOX);
    }

    const Block getByEncoding(char encoding) {
        for (Block block : registeredBlocks) {
            if (block.getEncoding() == encoding) return block;
        }
        if (encoding == '/' || encoding == '\\' || encoding == '|' || encoding == 'o') return AIR; // The static player defined in the level should not be part of the world
        return Block(Identifier("decoration", string(1, encoding)), encoding, BlockSettingsBuilder().nonSolid().build()); // Keep other characters as decoration
    }

private:
    Block registerBlock(Block& block) {
        registeredBlocks.push_back(block);
        return block;
    }
    vector<Block> registeredBlocks;
};