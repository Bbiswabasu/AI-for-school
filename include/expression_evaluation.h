#include <vector>
#include <string>
using namespace std;

class ExpressionEvaluation
{
public:
	vector<bool> done;
	vector<int> order_of_evaluation;
	string exp_to_display;

	ExpressionEvaluation();
	vector<int> get_order_of_evaluation() const;
	string get_exp_to_display() const;

	void init();
	int evaluate(int);
	void display_evaluation();
	bool check(int);
	void do_all_tasks();
	void startGame();
};