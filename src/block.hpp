#pragma once
#include "identifier.hpp"
#include "color.hpp"
#include "blockSettings.hpp"

class Block {
private:
    Identifier id_ = Identifier("adventure", "missing");
    char encoding_;
    Color color_;
    BlockSettings settings_;

public:
    /**
     * Constructs a block with the given identifier, encoding and settings.
     *
     * @param id The (unique) identifier of the block.
     * @param encoding The encoding of the block, which is the character used to represent it in the game world.
     * @param settings The settings of the block, which define how the block behaves in the game world.
     */
    Block(Identifier id, char encoding, BlockSettings settings) : Block(id, encoding, Color::RESET, settings) {}
    /**
     * Constructs a block with the given identifier, encoding, color and settings.
     *
     * @param id The (unique) identifier of the block.
     * @param encoding The encoding of the block, which is the character used to represent it in the game world.
     * @param color The color of the block.
     * @param settings The settings of the block, which define how the block behaves in the game world.
     */
    Block(Identifier id, char encoding, Color color, BlockSettings settings) {
        this->id_ = id;
        this->encoding_ = encoding;
        this->color_ = color;
        this->settings_ = settings;
    }

    /**
     * Returns the settings associated with the block.
     *
     * @return The settings of the block, including solidity, pushability, and more.
     */
    BlockSettings getSettings() {
        return settings_;
    }

    /**
     * Gets the identifier of the block.
     *
     * This identifier is used by the game to uniquely identify the block.
     *
     * @return The identifier of the block.
     */
    Identifier getId() {
        return id_;
    }

    /**
     * Returns the color of the block.
     *
     * The color is used when drawing the block in the world.
     *
     * @return The color of the block.
     */
    Color getColor() {
        return color_;
    }
    
    /**
     * Returns the character encoding of the block.
     *
     * This character is used in the text file as well as the terminal to represent the block.
     *
     * @return The character encoding of the block.
     */
    char getEncoding() {
        return encoding_;
    }
    
    /**
     * Sets the character encoding for the block.
     *
     * This encoding is used to represent the block in text files and the terminal.
     *
     * @param encoding The character encoding to set for the block.
     */
    void setEncoding(char encoding) {
        this->encoding_ = encoding;
    }

    std::ostream& operator<<(std::ostream& out) {
        out << encoding_;
        return out;
    }
    bool operator==(Block otherBlock) {
      return this->getId() == otherBlock.getId();
    }
};
