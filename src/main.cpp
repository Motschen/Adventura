#include <string>
#include <iostream>

#include <thread>
#include <chrono>

#include "world.hpp"
#include "player.hpp"
#include "blockRegistry.hpp"
#include "movementHandler.hpp"
#include "output.hpp"

using std::string;
using std::cout;
using std::endl;

bool startWorld(string worldFile);
vector<string> getOrderedFileNames(string dir);

bool testMode = false;
unsigned int worldIndex = 2;

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
            if (arg == "-h" || arg == "--help") 
                break;
            else if (arg == "-t" || arg == "--test") 
                testMode = true;
            
            else if ((arg == "-l" || arg == "--level") && argc > i + 1) {
                if (!startWorld("./worlds/" + string(argv[i+1])))
                    return 0; // Load only the specified world
                else
                    printFile("./screens/completed_single_level.txt", Color::BRIGHT_GREEN);
                return 0;
            }
        }
        if (!testMode) {
            printFile("./screens/help.txt", Color::BRIGHT_BLUE); // Print help screen
            return 0;
        }
    }
    if (!testMode) {
        printFile("./screens/start.txt", Color::BRIGHT_YELLOW);
        waitForInput();
        printGuide();
        waitForInput();
    }
    
    // Load every world in order
    for (const auto & world : getOrderedFileNames("./worlds"))
        if (!startWorld(world)) return 0;
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
    render(world, player.mapToWorldspace());
    
    inputLoop(player, world, testMode, worldIndex);

    worldIndex++;
    if (!player.isAlive()) printFile("./screens/death.txt", Color::BRIGHT_RED);
    return player.hasReachedGoal();
}