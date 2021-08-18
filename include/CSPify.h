#include <vector>
#include <deque>
using namespace std;

class CSPify
{
public:
    static vector<pair<pair<int, int>, int>> nodes;
    static vector<vector<vector<int>>> len;
    static vector<vector<vector<pair<int, int>>>> edges;
    static vector<vector<vector<vector<pair<int, int>>>>> graph;
    vector<vector<int>> vis;
    static deque<pair<pair<pair<int, int>, int>, pair<pair<int, int>, int>>> q;

    vector<pair<pair<int,int>,int>> get_nodes() const;

    CSPify();
    void init();
    void cspify();
    void print_graph();
    void do_all_tasks();
};