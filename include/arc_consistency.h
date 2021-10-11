#include <vector>
#include <queue>
#include <string>
#include <set>
using namespace std;

class ArcConsistency
{
public:
    int bag_size, num_nodes;
    vector<vector<vector<vector<int>>>> domain;
    vector<vector<int>> student_domain;
    vector<vector<int>> rebag;
    vector<pair<pair<int, int>, int>> nodes;
    set<pair<pair<int, int>, int>> nodes_set;
    vector<vector<string>> word_bag;
    queue<pair<pair<pair<int, int>, int>, pair<pair<int, int>, int>>> q;
    vector<int> result;
    vector<vector<int>> tick_cross;
    vector<vector<vector<pair<int, int>>>> consistency_graph;

    int get_bag_size() const;
    void set_bag_size(int);
    int get_num_nodes() const;
    void set_num_nodes(int);
    vector<pair<pair<int, int>, int>> get_nodes() const;
    vector<vector<int>> get_rebag() const;
    vector<vector<string>> get_word_bag() const;
    vector<int> get_result() const;
    vector<vector<int>> get_tick_cross() const;
    vector<vector<vector<pair<int, int>>>> get_consistency_graph() const;

    ArcConsistency();
    void init();
    void restore_bag(int, int, int);
    void restore_nodes(int, int, int);
    void choose();
    void print_bag();
    bool revise(pair<pair<int, int>, int>, pair<pair<int, int>, int>, bool);
    void add_node(pair<pair<int, int>, int>);
    void add_all_nodes();
    void build_queue();
    void ac3();
    void build_consistency_graph();
    void print_consistency_graph();
    void choose_x_nodes(int);
    void add_response(int, int, int);
    void check();
    void startGame();
};