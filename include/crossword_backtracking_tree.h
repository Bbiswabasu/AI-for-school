#include <bits/stdc++.h>
using namespace std;

class CrosswordBacktrackingTree
{
public:
    int node_id;
    vector<vector<int>> adj;                           //stores adjacency list of tree
    vector<vector<vector<char>>> grid_state;           //stores grid state at each node
    vector<vector<vector<vector<vector<int>>>>> domain_state; // stores domain of all nodes at each node of recursion tree
    void backtrack(int);
    void startGame();
};