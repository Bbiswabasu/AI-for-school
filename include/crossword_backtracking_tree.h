#include <vector>
#include "arc_consistency.h"
using namespace std;

class CrosswordBacktrackingTree
{
public:
    int node_id;
    int max_depth;
    int max_nodes;
    int bag_size;
    int repetition_allowed;                                   // stores if we will allow repetion
    vector<vector<int>> adj;                                  // stores adjacency list of tree
    vector<vector<vector<char>>> grid_state;                  // stores grid state at each node
    vector<vector<vector<vector<vector<int>>>>> domain_state; // stores domain of all nodes at each node of recursion tree
    vector<int> solution_indices;                             // stores index of nodes which are solution
    vector<int> reordered_nodes;
    vector<int> student_response;
    vector<int> result;
    ArcConsistency arc_con;

    int get_max_depth() const;
    void set_max_depth(int);
    int get_max_nodes() const;
    void set_max_nodes(int);
    int get_bag_size() const;
    void set_bag_size(int);
    vector<vector<int>> get_adj() const;
    vector<vector<vector<char>>> get_grid_state() const;
    vector<int> get_result() const;

    CrosswordBacktrackingTree();
    void backtrack(int, int);
    void random_order_nodes();
    void random_order_states();
    void preprocess();
    void add_response(int);
    void compute_filled_nodes(vector<vector<int>> &);
    bool is_valid_child(int, int,vector<vector<int>> &);
    void check();
    void do_all_tasks();
    void startGame();
};