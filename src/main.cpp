#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <thread>
#include <chrono>

#include "world.hpp"
#include "player.hpp"
#include "blockRegistry.hpp"
#include "movementHandler.hpp"

using std::string;
using std::cout;
using std::endl;
namespace fs = std::filesystem;

void render(World &world, Player &player);
void redraw(World &world, Player &player);
void jumpBackOneLine();
void printFile(string fileLocation, Color color);
bool startWorld(string worldFile);

/**
 * Entry point of the program.
 * If a world file is provided as an argument, play through that world.
 * Otherwise, play through all worlds in the worlds directory.
 * In case the player dies during gameplay, exit without printing the victory screen.
 * If the player reaches the goal of the final level, print the victory screen and exit.
 */
int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            string arg = string(argv[i]);
            if (arg == "-h" || arg == "--help") {
                printFile("./screens/help.txt", Color::BRIGHT_BLUE);
                return 0;
            }
            if ((arg == "-l" || arg == "--level") && argc > i + 1 && !startWorld("./worlds/" + string(argv[i+1]))) return 0;
        }
        
    }
    else {
        printFile("./screens/start.txt", Color::BRIGHT_YELLOW);
        waitForInput();
        vector<string> worlds;
        // Iterate over all files in the worlds directory
        for (auto & entry : fs::directory_iterator("./worlds")) {
            worlds.push_back(entry.path());
        }
        // We use this to sort the worlds alphabetically, so that the game progresses in the correct order.
        std::sort( worlds.begin(), worlds.end(), [](string a, string b) {
            return a < b;
        });
        // Load every world in order
        for (const auto & world : worlds)
            if (!startWorld(world)) return 0;
    }
    // Print the victory screen once all levels have been completed
    printFile("./screens/victory.txt", Color::BRIGHT_GREEN);

    return 0;
}

/**
 * Start a new world defined in the file at worldFile.
 * If the player reaches the goal, return true.
 * In case they die, print the death screen and return false.
 * @return true if the player reached the goal, false in case of death
 */
bool startWorld(string worldFile) {
    BlockRegistry blockRegistry = BlockRegistry();
    World world = World(blockRegistry);
    
    world.loadFromFile(worldFile);
    Player player = Player(world.getStartPos(), world);
    render(world, player);
    while (player.isAlive() && !player.hasReachedGoal()) {
        char lastChar;
        cin >> lastChar;
        if (onInput(lastChar, world, player)) redraw(world, player);
        else jumpBackOneLine();
    }
    if (!player.isAlive()) printFile("./screens/death.txt", Color::BRIGHT_RED);
    return player.hasReachedGoal();
}

/**
 * Move the console cursor up by one line.
 * Used to overwrite the previous line.
 */
void jumpBackOneLine() {
    std::cout << "\033[1A";
}

/**
 * Redraws the game world and player state on the console.
 * This function first moves the console cursor up by the number of lines
 * equivalent to the world's height, effectively clearing previous output.
 * It then calls the render function to display the current state of the world
 * and the player.
 *
 * @param world Reference to the World object representing the game's world.
 * @param player Reference to the Player object representing the player's state.
 */
void redraw(World &world, Player &player) {
    for (unsigned int y = 0; y <= world.getMaxY()+1; y++) {
        jumpBackOneLine();
    }
    render(world, player);
}

/**
 * Renders the current state of the game world and player onto the console.
 * It prints the world's blocks with their respective colors and encodings (characters).
 * On positions that overlap with the player texture, the relevant character of the player's texture is printed instead.
 */
void render(World &world, Player &player) {
    vector<vector<Block>> canvas = world.getFieldState();
    vector<vector<char>> playerTexture = player.mapToWorldspace();

    for (unsigned int y = 0; y <= world.getMaxY(); y++) {
        for (unsigned int x = 0; x <= world.getMaxX(); x++) {
            if (!world.getBlockAt(BlockPos(x, y)).getSettings().isPushable() 
                && playerTexture.size() > y && playerTexture.at(y).size() > x && playerTexture.at(y).at(x) != ' ') {
                cout << Color::BRIGHT_YELLOW << playerTexture.at(y).at(x);
            }
            else if (canvas.size() > y && canvas.at(y).size() > x) {
                cout << canvas.at(y).at(x).getColor() << canvas.at(y).at(x).getEncoding();
            }
            else cout << ' ';
        }
        cout << endl;
    }
}

/**
 * Prints the content of a file line by line onto the console,
 * in the specified color.
 * We use this to print our death and victory screens.
 *
 * @param fileLocation Path to the file to be printed.
 * @param color Color to be used for the output.
 */
void printFile(string fileLocation, Color color) {
    cout << color;
    vector<string> file = readFileAsVector(fileLocation);
    for (unsigned int y = 0; y < file.size(); y++) {
        cout << file.at(y) << endl;
    }
}