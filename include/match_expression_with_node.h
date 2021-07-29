#include <vector>
#include <string>
using namespace std;

class MatchExpression
{
public:
	vector<bool> done;
	vector<int> indices;

	vector<int> get_indices() const;

	MatchExpression();
	void init();
	string compute_expressions(int);
	void preprocessing();
	void startGame();
};