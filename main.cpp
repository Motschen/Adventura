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
bool parseArgs(int argc, char *argv[]);

static bool testMode = false;
static unsigned int worldIndex = 2;

/**
 * Entry point of the program.
 * If a world file is provided as an argument, play through that world.
 * Otherwise, play through all worlds in the worlds directory.
 * In case the player dies during gameplay, exit without printing the victory screen.
 * If the player reaches the goal of the final level, print the victory screen and exit.
 */
int main(int argc, char *argv[]) {
    if (parseArgs(argc, argv)) return 0;
    
    if (!testMode) {
        printFile("./start.screen.txt", Color::BRIGHT_YELLOW); // Show the story introduction
        waitForInput();
        printGuide(); // Show the block guide
        waitForInput();
    }
    
    // Load every world in order
    for (const auto & world : getOrderedFileNames("./", ".world.txt"))
        if (!startWorld(world)) return 0; // If the player dies, exit

    // Print the victory screen once all levels have been completed
    printFile("./victory.screen.txt", Color::BRIGHT_GREEN);

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
    if (!player.isAlive()) printFile("./death.screen.txt", Color::BRIGHT_RED);
    return player.hasReachedGoal();
}

/**
 * Parses command-line arguments to set the game's configuration.
 * 
 * Recognizes the following arguments:
 * - "-h" or "--help": Displays the help screen and exits.
 * - "-t" or "--test": Enables test mode, starting an automated playthrough.
 * - "-l" or "--level <levelName>": Loads and plays only the specified level. 
 * 
 * If a custom action is specified, the function returns true to indicate
 * immediate termination after executing the requested action.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array containing the command-line arguments.
 * @return true if the program should exit after handling the arguments, false otherwise.
 */
bool parseArgs(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            string arg = string(argv[i]); // Unsafe buffer usage warnings can be safely ignored, as we do check for the size
            if (arg == "-h" || arg == "--help") 
                break;
            else if (arg == "-t" || arg == "--test") 
                testMode = true;
            
            else if ((arg == "-l" || arg == "--level") && argc > i + 1) {
                if (!startWorld("./" + string(argv[i+1]))) // This warning can also be ignored, again – we do this in a safe way
                    return true; // Load only the specified world
                else
                    printFile("./completed_single_level.screen.txt", Color::BRIGHT_GREEN);
                return true;
            }
        }
        if (!testMode) {
            printFile("./help.screen.txt", Color::BRIGHT_BLUE); // Print help screen
            return true;
        }
    }
    return false;
}
