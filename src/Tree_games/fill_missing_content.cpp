#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "fill_missing_content.h"
#include "expression_evaluation.h"
#include "dag_generator.h"

using namespace std;

MissingContent::MissingContent() {}
int MissingContent::get_cnt_op() const { return cnt_op; }
void MissingContent::set_cnt_op(int x_) { cnt_op = x_; }
int MissingContent::get_cnt_var() const { return cnt_var; }
void MissingContent::set_cnt_var(int x_) { cnt_var = x_; }

void MissingContent::backup_data()
{
	ExpressionEvaluation exp;
	exp.init();
	exp.evaluate(0);

	orig_content = DAGGenerator::content;
	orig_values = DAGGenerator::values;
}
void MissingContent::restore_data()
{
	DAGGenerator::content = orig_content;
	DAGGenerator::values = orig_values;
}
void MissingContent::miss_content()
{
	vector<int> index;
	for (int i = 0; i < DAGGenerator::num_nodes; i++)
		index.push_back(i);
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(index.begin(), index.end(), default_random_engine(seed));

	int cnt_op_ = cnt_op, cnt_var_ = cnt_var;
	for (int i = 0; i < DAGGenerator::num_nodes; i++)
	{
		if (DAGGenerator::adj[index[i]].size() == 0)
			DAGGenerator::content[index[i]] = to_string(DAGGenerator::values[index[i]]);
		if (cnt_op_ > 0 && DAGGenerator::adj[index[i]].size() != 0)
		{
			DAGGenerator::content[index[i]] = "?";
			cnt_op_--;
		}
		if (cnt_var_ > 0 && DAGGenerator::adj[index[i]].size() == 0)
		{
			DAGGenerator::content[index[i]] = "?";
			cnt_var_--;
		}
	}
}
void MissingContent::change_content(int node, string s)
{
	DAGGenerator::content[node] = s;
	if (DAGGenerator::adj[node].size() == 0)
		DAGGenerator::values[node] = stoi(s);
}
bool MissingContent::check()
{
	ExpressionEvaluation exp;
	exp.init();
	exp.evaluate(0);
	return orig_values[0] == DAGGenerator::values[0];
}
void MissingContent::startGame()
{
	cout << "Enter number of operators to miss : ";
	cin >> cnt_op;
	cout << "Enter number of variables to miss : ";
	cin >> cnt_var;
	backup_data();
	miss_content();

	DAGGenerator dag_gen;
	dag_gen.display_dag();
	cout << "Fill missing content of nodes such that the given values are satisfied : \n";
	for (int i = 0; i < cnt_op + cnt_var; i++)
	{
		int node;
		string s;
		cin >> node >> s;
		change_content(node, s);
	}

	bool correct = check();
	// for (int i = 0; i < DAGGenerator::adj.size(); i++)
	// {
	// 	if (values_mem[i] != DAGGenerator::values[i])
	// 	{
	// 		wrong = 1;
	// 		break;
	// 	}
	// }
	if (!correct)
		cout << "WRONG\n";
	else
		cout << "CORRECT\n";
	restore_data();
}