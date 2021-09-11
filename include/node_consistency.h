#include <vector>
using namespace std;

class NodeConsistency
{
public:
	vector<vector<int>> rebag;			 //rebag[i] = index of words taken from length i
	vector<pair<int, int>> shuffled_bag; //stores all words as {length,index} pair
	vector<vector<int>> student_answers;
	vector<bool> result;

	void init();
	void choose();
	void print_bag();
	void add_response(int, int);
	void check();
	void startGame();
};