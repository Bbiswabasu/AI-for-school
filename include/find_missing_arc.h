#include <vector>
using namespace std;

class FindMissingArc
{
public:
    vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> arcs_to_display;
    pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>> answer, student_answer;

    vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> get_arcs_to_display() const;
    pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>> get_answer() const;

    FindMissingArc();
    void choose_arc();
    bool check(int, int, char, int, int, char);
    void startGame();
};