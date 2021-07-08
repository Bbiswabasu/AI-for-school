#include <bits/stdc++.h>
using namespace std;

class CrosswordGenerator
{
public:
    static int grid_size; 
    static vector<vector<char>> grid;
    static vector<pair<int,int>> moves;

    void init();
    void form_grid();
    void print_grid();
    void transpose();
    void remove2();
    void remove1();
    void distribution(); 
    void adjust();
};