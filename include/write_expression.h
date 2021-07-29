#include "bddObj.h"

using namespace std;

class WriteExpression
{
public:
    vector<int> matching; //Stores index of matching ')' for each '('
    BDD buildBDDFromAdj(int, bddMgr &, vector<BDD> &);
    BDD buildBDDFromStr(int, bddMgr &, vector<BDD> &, string &, vector<int> &);
    void expressionParser(string &);
    bool verifyAnswer(string&);
    void startGame();
};