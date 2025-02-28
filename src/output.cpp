#include <string>
#include <iostream>

#include "output.hpp"

using std::string;
using std::cout;
using std::endl;

/**
 * Move the console cursor up by one line.
 * Used to overwrite the previous line.
 */
static void jumpBackOneLine() {
    std::cout << "\033[1A";
}

/**
 * Renders the current state of the game world and player onto the console.
 * It prints the world's blocks with their respective colors and encodings (characters).
 * On positions that overlap with the player texture, the relevant character of the player's texture is printed instead.
 * 
 * @param world Reference to the World object representing the current world.
 * @param playerTexture Reference to the current Player texture.
 */
static vector<vector<char>> render(World &world, vector<vector<char>> playerTexture) {
    vector<vector<Block>> canvas = world.getFieldState();
    vector<vector<char>> out;

    for (unsigned int y = 0; y <= world.getMaxY(); y++) {
        vector<char> line;
        for (unsigned int x = 0; x <= world.getMaxX(); x++) {
            if (!world.getBlockAt(BlockPos(x, y)).getSettings().isPushable() 
                && playerTexture.size() > y && playerTexture.at(y).size() > x && playerTexture.at(y).at(x) != ' ') {
                line.push_back(playerTexture.at(y).at(x));
                //<< Color::BRIGHT_YELLOW << playerTexture.at(y).at(x);
            }
            else if (canvas.size() > y && canvas.at(y).size() > x) {
                line.push_back(canvas.at(y).at(x).getEncoding());
                //cout << canvas.at(y).at(x).getColor() << canvas.at(y).at(x).getEncoding();
            }
            else line.push_back(' ');
        }
        out.push_back(line);
    }
    return out;
}

/**
 * Prints a guide for the player, explaining what each block in the game
 * represents.
 */
static void printGuide() {
    // We use a vector here instead of a map, because we want to keep this order
    std::vector<std::pair<string, Color>> guide = {
        {"- Plattform", Color::RESET},
        {"H Leiter",    Color::BRIGHT_MAGENTA},
        {"S Start",     Color::RESET},
        {"O Ziel",      Color::BRIGHT_GREEN},
        {"0 Wand",      Color::RESET},
        {"^ Stacheln",  Color::BRIGHT_RED},
        {"~ Wasser",    Color::BRIGHT_BLUE},
        {"x Kiste",     Color::BRIGHT_CYAN},
        {"* Sand",      Color::BRIGHT_YELLOW}
    };
    for (std::pair<string, Color> p : guide) {
        cout << p.second << p.first << endl;
    }
    cout << endl << Color::RESET << "WASD + Enter -> Spiel starten" << endl;
}
