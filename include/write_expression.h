#include <bits/stdc++.h>
#include "bddObj.h"

using namespace std;

class WriteExpression
{
public:
    BDD build(int node,bddMgr& mgr);
	void startGame();
};