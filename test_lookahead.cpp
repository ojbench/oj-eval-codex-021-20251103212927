#include <iostream>
#include <fstream>
#include <vector>
#include "game.h"

using namespace std;

void testSequence(Game *game, vector<char> seq) {
    cout << "Sequence: ";
    for (char c : seq) cout << c << " ";
    
    int total_reward = 0;
    for (char op : seq) {
        int reward = game->play(op);
        total_reward += reward;
    }
    
    cout << "-> Total reward: " << total_reward;
    cout << ", Bricks hit: " << game->bricksHit();
    cout << ", Remaining: " << game->bricksRemaining() << endl;
}

int main() {
    // Test all 3-step sequences
    const char ops[] = {'A', 'B', 'C', 'D', 'E'};
    
    vector<vector<char>> best_seqs;
    int best_bricks = -1;
    int best_score = -1;
    
    for (char op1 : ops) {
        for (char op2 : ops) {
            for (char op3 : ops) {
                ifstream input("/workspace/data/021/testcases/naive.in");
                Game *game = new Game(input);
                
                vector<char> seq = {op1, op2, op3};
                int total_reward = 0;
                
                for (char op : seq) {
                    int reward = game->play(op);
                    total_reward += reward;
                }
                
                int bricks_hit = game->bricksHit();
                
                if (bricks_hit > best_bricks || 
                    (bricks_hit == best_bricks && total_reward > best_score)) {
                    if (bricks_hit > best_bricks) {
                        best_seqs.clear();
                    }
                    best_bricks = bricks_hit;
                    best_score = total_reward;
                    best_seqs.push_back(seq);
                }
                
                delete game;
            }
        }
    }
    
    cout << "Best sequences (" << best_bricks << " bricks, score " << best_score << "):" << endl;
    for (auto &seq : best_seqs) {
        ifstream input("/workspace/data/021/testcases/naive.in");
        Game *game = new Game(input);
        testSequence(game, seq);
        delete game;
    }
    
    return 0;
}
