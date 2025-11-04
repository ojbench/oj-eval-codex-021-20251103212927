#include <iostream>
#include <fstream>
#include <vector>
#include "game.h"

using namespace std;

int main() {
    ifstream input("/workspace/data/021/testcases/naive.in");
    Game *game = new Game(input);
    
    const char ops[] = {'A', 'B', 'C', 'D', 'E'};
    
    cout << "Initial state: " << game->bricksRemaining() << " bricks remaining" << endl;
    
    Game::Save* initial = game->save();
    
    cout << "\nTrying each operation:" << endl;
    for (char op : ops) {
        game->load(initial);
        int reward = game->play(op);
        int remaining = game->bricksRemaining();
        int hit = game->bricksHit();
        
        cout << "Op " << op << ": reward=" << reward << ", hit=" << hit << ", remaining=" << remaining << endl;
    }
    
    game->load(initial);
    game->erase(initial);
    
    delete game;
    return 0;
}
