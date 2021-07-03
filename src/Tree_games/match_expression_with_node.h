#include <bits/stdc++.h>
using namespace std;

class MatchExpression
{
public:
	vector<bool> done;
	MatchExpression();
	string compute_expressions(int);
	void startGame();
};