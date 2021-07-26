#include <vector>
using namespace std;

class FindCrosswordNodes
{
public:
    vector<pair<int, int>> nodes_across;
    vector<pair<int, int>> nodes_down;
    void check();
    void startGame();
};