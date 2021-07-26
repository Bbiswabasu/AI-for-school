#include <vector>
using namespace std;

class DrawCrosswordGraph
{
public:
	vector<vector<vector<vector<pair<int, int>>>>> graph;
	void check();
	void startGame();
};