#include <vector>
#include <queue>
using namespace std;

class ArcConsistency
{
public:
    int szbag;
    vector<vector<vector<vector<int>>>> domain;
    vector<vector<int>> rebag;
    vector<pair<pair<int, int>, int>> nodes;
    queue<pair<pair<pair<int, int>, int>, pair<pair<int, int>, int>>> q;

    void init();
    void choose();
    void print_bag();
    bool revise(pair<pair<int, int>, int>, pair<pair<int, int>, int>);
    void add_node(pair<pair<int, int>, int>);
    void add_all_nodes();
    void ac3();
    void choose_x_nodes(int);
    void startGame();
};