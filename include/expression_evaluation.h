#include <vector>
using namespace std;

class ExpressionEvaluation
{
public:
	vector<bool> done;
	vector<int> order_of_evaluation;

	ExpressionEvaluation();
	vector<int> get_order_of_evaluation() const;
	
	void init();
	int evaluate(int);
	void display_evaluation();
	void startGame();
};