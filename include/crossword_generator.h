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

    int get_grid_size() const;
    void set_grid_size(int);
    vector<vector<char>> get_grid() const;

    CrosswordGenerator();
    void restore_grid(int, int, char);
    void build_bag();
    void init();
    int random(int, int, int);
    void form_grid();
    void print_grid();
    void transpose();
    void remove2();
    void remove1();
    void do_all_tasks();
};