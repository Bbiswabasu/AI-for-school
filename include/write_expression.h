#include "bddObj.h"

using namespace std;

class WriteExpression
{
public:
    vector<int> matching; //Stores index of matching ')' for each '('
    string syntax_error;

    WriteExpression();
    BDD buildBDDFromAdj(int, bddMgr &, vector<BDD> &);
    BDD buildBDDFromStr(string &, bddMgr &, vector<BDD> &);
    bool check(string);
    bool syntax_check(string &);
    void startGame();
};