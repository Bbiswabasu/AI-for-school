#include <bits/stdc++.h>
using namespace std;

class ArcConsistency
{
public:
    int szbag;
    vector<vector<vector<vector<int>>>> notdom; 
    vector<int> bagct;
    vector<vector<int>> rebag;

    void choose();
    void print_bag();
    bool revise(pair<pair<int,int>,int>,pair<pair<int,int>,int>);
    void ac3();
	void startGame();
};