#include <bits/stdc++.h>
using namespace std;

class CrosswordGenerator
{
public:
    static int grid_size; 
    static vector<vector<char>> grid;
    static vector<pair<int,int>> moves;
    static vector<vector<string>> bag;
    static int uplen;

    void init();
    void form_grid();
    void print_grid();
    void transpose();
    void remove2();
    void remove1();
    void remove_long_words();
    void distribution(); 
    void adjust();
};