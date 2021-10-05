#include <vector>
#include <string>
using namespace std;

class NodeConsistency
{
public:
	vector<vector<int>> rebag;				 //rebag[i] = index of words taken from length i
	vector<pair<int, int>> shuffled_bag_ind; //stores all words as {length,index} pair
	vector<string> shuffled_bag;
	vector<vector<int>> student_answers;
	vector<int> result;
	vector<vector<int>> tick_cross;

	vector<pair<int, int>> get_shuffled_bag_ind() const;
	vector<string> get_shuffled_bag() const;
	vector<int> get_result() const;
	vector<vector<int>> get_tick_cross() const;

	NodeConsistency();
	void init();
	void restore_bag(int, int);
	void choose();
	void print_bag();
	void add_response(int, int);
	void check();
	void startGame();
};