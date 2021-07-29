#include <vector>
using namespace std;

class ExpressionEvaluation
{
public:
	vector<bool> done;
	ExpressionEvaluation();
	void init();
	int evaluate(int);
	void startGame();
};