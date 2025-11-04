#include <iostream>
#include <fstream>
#include "game.h"

using namespace std;

int main() {
    ifstream input("/workspace/data/021/testcases/naive.in");
    Game *game = new Game(input);
    
    cout << "n=" << game->n << ", m=" << game->m << ", s=" << game->s << endl;
    cout << "Total bricks: " << game->bricksTotal() << endl;
    cout << "Remaining bricks: " << game->bricksRemaining() << endl;
    
    // Test expected sequence: B, D, A
    cout << "\nTesting B:" << endl;
    int r1 = game->play('B');
    cout << "Reward: " << r1 << ", Remaining: " << game->bricksRemaining() << endl;
    
    cout << "\nTesting D:" << endl;
    int r2 = game->play('D');
    cout << "Reward: " << r2 << ", Remaining: " << game->bricksRemaining() << endl;
    
    cout << "\nTesting A:" << endl;
    int r3 = game->play('A');
    cout << "Reward: " << r3 << ", Remaining: " << game->bricksRemaining() << endl;
    
    cout << "\nTotal reward: " << (r1 + r2 + r3) << endl;
    
    delete game;
    return 0;
}
