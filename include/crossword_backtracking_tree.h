#include <vector>
using namespace std;

class CrosswordBacktrackingTree
{
public:
    int node_id;
    int repetion_allowed;                                     //stores if we will allow repetion
    vector<vector<int>> adj;                                  //stores adjacency list of tree
    vector<vector<vector<char>>> grid_state;                  //stores grid state at each node
    vector<vector<vector<vector<vector<int>>>>> domain_state; //stores domain of all nodes at each node of recursion tree
    vector<int> solution_indices;                             //stores index of nodes which are solution
    void backtrack(int);
    void startGame();
};