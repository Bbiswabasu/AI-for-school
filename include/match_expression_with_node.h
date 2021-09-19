#include <vector>
#include <string>
using namespace std;

class MatchExpression
{
public:
	vector<bool> done;
	vector<int> indices;
	vector<string> exp_to_display;
	vector<int> student_response, correct_response, wrong_response, correct_answers;

	vector<int> get_indices() const;
	vector<string> get_exp_to_display() const;
	vector<int> get_student_response() const;
	vector<int> get_correct_response() const;
	vector<int> get_wrong_response() const;
	vector<int> get_correct_answers() const;

	MatchExpression();
	void init();
	void restore_exp(int, int);
	string compute_expressions(int);
	void preprocessing();
	void add_response(int);
	void check();
	void startGame();
};