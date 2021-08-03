#include <vector>
using namespace std;

class FindCrosswordNodes
{
public:
    vector<pair<int, int>> nodes_across;
    vector<pair<int, int>> nodes_down;
    vector<pair<pair<int, int>, char>> missed_nodes, wrong_nodes, correct_nodes;

    vector<pair<int, int>> get_nodes_across() const;
    vector<pair<int, int>> get_nodes_down() const;
    vector<pair<pair<int, int>, char>> get_missed_nodes() const;
    vector<pair<pair<int, int>, char>> get_wrong_nodes() const;
    vector<pair<pair<int, int>, char>> get_correct_nodes() const;

    FindCrosswordNodes();
    bool check();
    void display_result();
    void startGame();
};