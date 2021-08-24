#include <vector>
#include <string>
using namespace std;

class MissingContent
{
public:
	int cnt_op, cnt_var;
	vector<string> orig_content;
	vector<int> orig_values;

	int get_cnt_op() const;
	void set_cnt_op(int);
	int get_cnt_var() const;
	void set_cnt_var(int);

	MissingContent();
	void backup_data();
	void restore_data();
	void miss_content();
	void change_content(int, string);
	bool check();
	void startGame();
};