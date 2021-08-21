#include <vector>
using namespace std;

class DrawCrosswordGraph
{
public:
	vector<vector<vector<vector<pair<int, int>>>>> graph;

	vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> missed_edges, wrong_edges, correct_edges;

	vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> get_missed_edges() const;
	vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> get_wrong_edges() const;
	vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> get_correct_edges() const;
	
	DrawCrosswordGraph();
	void init();
	bool check();
	void display_result();
	void add_edge(int, int, int, int, int, int);
	void startGame();
};