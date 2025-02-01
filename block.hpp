#pragma once
#include "identifier.hpp"
#include "color.hpp"
#include "blockSettings.hpp"

class Block {
private:
    Identifier id = Identifier("adventure", "missing");
    char encoding;
    Color color;
    BlockSettings settings;

public:
    Block(Identifier id, char encoding, BlockSettings settings) : Block(id, encoding, Color::RESET, settings) {};
    Block(Identifier id, char encoding, Color color, BlockSettings settings) {
        this->id = id;
        this->encoding = encoding;
        this->color = color;
        this->settings = settings;
    };

    BlockSettings getSettings() {
        return settings;
    }

    Identifier getId() {
        return id;
    }
    Color getColor() {
        return color;
    }
    char getEncoding() {
        return encoding;
    }
    void setEncoding(char encoding) {
        this->encoding = encoding;
    }

    std::ostream& operator<<(std::ostream& out) {
        out << encoding;
        return out;
    }
    bool operator==(Block otherBlock) {
      return this->getId() == otherBlock.getId();
    }
};
