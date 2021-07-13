#include <bits/stdc++.h>
using namespace std;

class ArcConsistency
{
public:
    void choose();
    void print_bag();
    bool revise(pair<pair<int,int>,int>,pair<pair<int,int>,int>);
    void ac3();
	void startGame();
};