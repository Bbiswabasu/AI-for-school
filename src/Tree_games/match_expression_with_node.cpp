//Implementation of the match expression with node game

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "dag_generator.h"
#include "match_expression_with_node.h"

using namespace std;

MatchExpression::MatchExpression()
{
	done.resize(DAGGenerator::adj.size(), 0);
}

vector<int> MatchExpression::get_indices() const { return indices; }
vector<string> MatchExpression::get_exp_to_display() const { return exp_to_display; }
vector<int> MatchExpression::get_student_response() const { return student_response; }
vector<int> MatchExpression::get_correct_response() const { return correct_response; }
vector<int> MatchExpression::get_wrong_response() const { return wrong_response; }
vector<int> MatchExpression::get_correct_answers() const { return correct_answers; }

void MatchExpression::init()
{
	done.resize(DAGGenerator::adj.size(), 0);
}
string MatchExpression::compute_expressions(int node)
{
	if (done[node])
		return DAGGenerator::expressions[node];
	if (DAGGenerator::adj[node].size() == 0)
	{
		done[node] = 1;
		return DAGGenerator::expressions[node] = DAGGenerator::content[node];
	}
	if (DAGGenerator::adj[node].size() == 1)
	{
		DAGGenerator::expressions[node] = "( ~ " + compute_expressions(DAGGenerator::adj[node][0]) + " )";
		done[node] = 1;
		return DAGGenerator::expressions[node];
	}
	string ans = "( ";
	ans += compute_expressions(DAGGenerator::adj[node][0]) + " ";
	ans += DAGGenerator::content[node] + " ";
	ans += compute_expressions(DAGGenerator::adj[node][1]) + " ";
	ans += ")";
	DAGGenerator::expressions[node] = ans;
	done[node] = 1;
	return ans;
}

void MatchExpression::preprocessing()
{
	compute_expressions(0);
	indices.resize(DAGGenerator::num_nodes);
	for (int i = 0; i < DAGGenerator::num_nodes; i++)
		indices[i] = i;
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(indices.begin(), indices.end(), default_random_engine(seed));

	for (int i = 0; i < DAGGenerator::num_nodes; i++)
	{
		if (DAGGenerator::adj[indices[i]].size() != 0)
		{
			exp_to_display.push_back(DAGGenerator::expressions[indices[i]]);
			cout << exp_to_display.back() << "\n";
		}
	}
}
void MatchExpression::add_response(int n)
{
	student_response.push_back(n);
}
void MatchExpression::check()
{
	int j = 0;
	for (int i = 0; i < exp_to_display.size(); i++)
	{
		while (DAGGenerator::adj[indices[j]].size() == 0)
			j++;
		if (exp_to_display[i] == DAGGenerator::expressions[student_response[i]])
			correct_response.push_back(i);
		else
		{
			wrong_response.push_back(i);
			correct_answers.push_back(indices[j]);
		}
		j++;
	}
}
void MatchExpression::startGame()
{
	preprocessing();
	cout << "Match each expression with corresponding node number : \n";
	bool correct = 1;
	for (int i = 0; i < exp_to_display.size(); i++)
	{
		int n;
		cin >> n;
		add_response(n);
	}
	check();
	if (wrong_response.size() == 0)
		cout << "CORRECT\n";
	else
	{
		cout << "Correct response: ";
		for (auto it : correct_response)
			cout << it << " ";
		cout << "\nWrong response\n";
		for (int i = 0; i < wrong_response.size(); i++)
		{
			cout << wrong_response[i] << " - " << correct_answers[i] << "\n";
		}
	}
}