#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <random>
#include "game.h"

using namespace std;

int main() {
    Game *game = new Game(cin);
    
    vector<char> operations;
    const char ops[] = {'A', 'B', 'C', 'D', 'E'};
    int n = game->n;
    int max_ops = game->m;
    
    // More sophisticated strategy:
    // 1. Try different moves and pick the one that gives best immediate reward
    // 2. Use save/load to explore options
    
    int op_count = 0;
    int prev_bricks = game->bricksRemaining();
    
    while (game->bricksRemaining() > 0 && op_count < max_ops) {
        int best_reward = -1;
        char best_op = 'C';
        
        // Try each operation and see which gives best reward
        Game::Save* current_save = game->save();
        
        for (char op : ops) {
            game->load(current_save);
            int reward = game->play(op);
            
            if (reward > best_reward) {
                best_reward = reward;
                best_op = op;
            }
        }
        
        // Apply the best operation
        game->load(current_save);
        game->erase(current_save);
        game->play(best_op);
        operations.push_back(best_op);
        op_count++;
        
        // If no progress for a while, try a random move
        if (game->bricksRemaining() == prev_bricks && op_count % 5 == 0) {
            // Add some randomness
            int random_idx = rand() % 5;
            best_op = ops[random_idx];
        }
        prev_bricks = game->bricksRemaining();
    }
    
    // Output all operations
    for (char op : operations) {
        cout << op << endl;
    }
    
    delete game;
    return 0;
}
