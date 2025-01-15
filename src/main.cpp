#include <string>
#include <iostream>
#include <filesystem>
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
bool startWorld(string worldFile);

int main() {
    for (const auto & entry : fs::directory_iterator("./worlds"))
        if (!startWorld(entry.path())) return 0;
    
    return 0;
}
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
    return player.hasReachedGoal();
}
void jumpBackOneLine() {
    std::cout << "\033[1A";
}

void redraw(World &world, Player &player) {
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    for (unsigned int y = 0; y <= world.getMaxY()+1; y++) {
        jumpBackOneLine();
    }
    render(world, player);
}

void render(World &world, Player &player) {
    vector<vector<Block>> canvas = world.getFieldState();
    vector<vector<char>> playerTexture = player.mapToWorldspace();

    for (unsigned int y = 0; y <= world.getMaxY(); y++) {
        for (unsigned int x = 0; x <= world.getMaxX(); x++) {
            if (playerTexture.size() > y && playerTexture.at(y).size() > x && playerTexture.at(y).at(x) != ' ') {
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