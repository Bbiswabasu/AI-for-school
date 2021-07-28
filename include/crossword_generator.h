#include <vector>
#include <string>
using namespace std;

class CrosswordGenerator
{
public:
    static int grid_size;
    static vector<vector<char>> grid;
    static vector<pair<int, int>> moves;
    static vector<vector<string>> bag;
    static int uplen;

    void init();
    int random(int, int);
    void form_grid();
    void print_grid();
    void transpose();
    void remove2();
    void remove1();
    void distribution();
    void generate_crossword();
};