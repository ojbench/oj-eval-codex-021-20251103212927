#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include "game.h"

using namespace std;

struct SearchState {
    Game::Save* save;
    vector<char> moves;
    int bricks_hit;
    int score;
};

int main() {
    Game *game = new Game(cin);
    
    vector<char> operations;
    const char ops[] = {'A', 'B', 'C', 'D', 'E'};
    int max_ops = game->m;
    
    int op_count = 0;
    int total_bricks = game->bricksTotal();
    
    // Use a deeper lookahead for small problems, greedy for large ones
    int lookahead_depth = (game->n <= 10) ? 3 : 1;
    
    while (game->bricksRemaining() > 0 && op_count < max_ops) {
        int best_bricks_hit = -1;
        int best_score = -1;
        char best_op = 'C';
        
        Game::Save* current_save = game->save();
        
        if (lookahead_depth == 1 || op_count > max_ops - 10) {
            // Simple greedy
            for (char op : ops) {
                int reward = game->play(op);
                int bricks_hit = game->bricksHit();
                
                if (bricks_hit > best_bricks_hit || 
                    (bricks_hit == best_bricks_hit && reward > best_score)) {
                    best_bricks_hit = bricks_hit;
                    best_score = reward;
                    best_op = op;
                }
                
                game->load(current_save);
            }
        } else {
            // Multi-step lookahead using BFS
            queue<SearchState> q;
            
            for (char op : ops) {
                int reward = game->play(op);
                int bricks_hit = game->bricksHit();
                
                SearchState state;
                state.save = game->save();
                state.moves.push_back(op);
                state.bricks_hit = bricks_hit;
                state.score = reward;
                q.push(state);
                
                game->load(current_save);
            }
            
            while (!q.empty() && q.front().moves.size() < lookahead_depth) {
                SearchState curr = q.front();
                q.pop();
                
                game->load(curr.save);
                
                for (char op : ops) {
                    int reward = game->play(op);
                    int bricks_hit = game->bricksHit();
                    
                    SearchState next;
                    next.save = game->save();
                    next.moves = curr.moves;
                    next.moves.push_back(op);
                    next.bricks_hit = bricks_hit;
                    next.score = curr.score + reward;
                    q.push(next);
                    
                    game->load(curr.save);
                }
                
                game->erase(curr.save);
            }
            
            // Find the best path
            while (!q.empty()) {
                SearchState state = q.front();
                q.pop();
                
                if (state.bricks_hit > best_bricks_hit || 
                    (state.bricks_hit == best_bricks_hit && state.score > best_score)) {
                    best_bricks_hit = state.bricks_hit;
                    best_score = state.score;
                    best_op = state.moves[0];
                }
                
                game->erase(state.save);
            }
        }
        
        game->erase(current_save);
        
        // Apply the best operation
        game->play(best_op);
        operations.push_back(best_op);
        op_count++;
    }
    
    // Output all operations
    for (char op : operations) {
        cout << op << endl;
    }
    
    delete game;
    return 0;
}
