#include "bddObj.h"

using namespace std;

class WriteExpression
{
public:
    vector<int> matching; //Stores index of matching ')' for each '('

    WriteExpression();
    void init();
    BDD buildBDDFromAdj(int, bddMgr &, vector<BDD> &);
    BDD buildBDDFromStr(int, bddMgr &, vector<BDD> &, string &, vector<int> &);
    void expression_parser(string);
    bool check(string);
    void startGame();
};