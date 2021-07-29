#include <string>
#include <set>
#include <vector>
using namespace std;
class TruthTable
{
public:
    int num_vars;
    string expression;
    set<char> vars;
    vector<vector<int>> adj;
    void start();
    int evaluateFromStr(int ,string &,vector<int> &);
};