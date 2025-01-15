#pragma once
#include <vector>
#include <string>
#include "block.hpp"

using std::vector;
using std::string;

class BlockRegistry {
public:
    Block AIR = Block(Identifier("adventura", "air"), ' ', BlockSettingsBuilder().nonSolid().build());
    Block PLATFORM = Block(Identifier("adventura", "platform"), '-', BlockSettingsBuilder().build());
    Block LADDER = Block(Identifier("adventura", "ladder"), 'H', BlockSettingsBuilder().climbableFromBottom().climbableFromTop().build());
    Block START = Block(Identifier("adventura", "start"), 'S', BlockSettingsBuilder().build());
    Block GOAL = Block(Identifier("adventura", "goal"), 'O', BlockSettingsBuilder().build());

    BlockRegistry() {
        registerBlock(AIR);
        registerBlock(PLATFORM);
        registerBlock(LADDER);
        registerBlock(START);
        registerBlock(GOAL);   
    }

    const Block getByEncoding(char encoding) {
        for (Block block : registeredBlocks) {
            if (block.getEncoding() == encoding) return block;
        }
        return AIR;
    }

private:
    Block registerBlock(Block& block) {
        registeredBlocks.push_back(block);
        return block;
    }
    vector<Block> registeredBlocks;
};