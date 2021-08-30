//Implementation of the evaluating expression game

#include <iostream>
#include "dag_generator.h"
#include "expression_evaluation.h"
#include "match_expression_with_node.h"

using namespace std;

ExpressionEvaluation::ExpressionEvaluation()
{
	done.resize(DAGGenerator::adj.size(), 0);
}
vector<int> ExpressionEvaluation::get_order_of_evaluation() const { return order_of_evaluation; }
string ExpressionEvaluation::get_exp_to_display() const { return exp_to_display; }

void ExpressionEvaluation::init()
{
	done.resize(DAGGenerator::adj.size(), 0);
	order_of_evaluation.clear();
}

int ExpressionEvaluation::evaluate(int node)
{
	if (done[node])
		return DAGGenerator::values[node];
	if (DAGGenerator::adj[node].size() == 0)
	{
		order_of_evaluation.push_back(node);
		done[node] = 1;
		return DAGGenerator::values[node];
	}
	int ans;
	if (DAGGenerator::adj[node].size() == 1)
	{
		ans = !(evaluate(DAGGenerator::adj[node][0]));
		order_of_evaluation.push_back(node);
		DAGGenerator::values[node] = ans;
		done[node] = 1;
		return ans;
	}
	int left = evaluate(DAGGenerator::adj[node][0]);
	int right = evaluate(DAGGenerator::adj[node][1]);
	if (DAGGenerator::content[node] == "&")
		ans = left & right;
	else if (DAGGenerator::content[node] == "|")
		ans = left | right;
	else if (DAGGenerator::content[node] == "=>")
		ans = (!left) | right;
	else if (DAGGenerator::content[node] == "<=>")
		ans = ((!left) & (!right)) | (left & right);
	order_of_evaluation.push_back(node);
	DAGGenerator::values[node] = ans;
	done[node] = 1;
	return ans;
}

void ExpressionEvaluation::display_evaluation()
{
	for (auto node : order_of_evaluation)
		cout << node << " -> " << DAGGenerator::values[node] << "\n";
}

bool ExpressionEvaluation::check(int n)
{
	return DAGGenerator::values[0] == n;
}
void ExpressionEvaluation::do_all_tasks()
{
	MatchExpression mat;
	mat.init();
	mat.compute_expressions(0);
	exp_to_display = DAGGenerator::expressions[0];
	init();
	evaluate(0);
}

void ExpressionEvaluation::startGame()
{
	do_all_tasks();
	cout << exp_to_display << "\n";

	int num_node = DAGGenerator::adj.size();
	cout << "Enter the value of given expression when :\n";
	for (int i = 0; i < num_node; i++)
	{
		if (DAGGenerator::adj[i].size() == 0)
			cout << DAGGenerator::content[i] << " = " << DAGGenerator::values[i] << ", ";
	}
	cout << "\n";

	int user_value;
	cin >> user_value;
	if (check(user_value))
		cout << "CORRECT\n";
	else
		cout << "WRONG\n";

	display_evaluation();
}