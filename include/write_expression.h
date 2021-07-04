#include <bits/stdc++.h>
#include "bddObj.h"

using namespace std;

class WriteExpression
{
public:
    BDD buildBDDFromAdj(int, bddMgr&, vector<BDD>&);
    BDD buildBDDFromStr(int, bddMgr&, vector<BDD>&, string&, vector<int>&);
    void expressionParser(string&);
    bool verifyAnswer();
	void startGame();
};