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
			cout << DAGGenerator::expressions[indices[i]] << "\n";
	}
}

void MatchExpression::startGame()
{
	preprocessing();
	cout << "Match each expression with corresponding node number : \n";
	bool correct = 1;
	for (int i = 0; i < DAGGenerator::num_nodes; i++)
	{
		if (DAGGenerator::adj[indices[i]].size() == 0)
			continue;
		int n;
		cin >> n;
		if (DAGGenerator::expressions[n] != DAGGenerator::expressions[indices[i]])
		{
			correct = 0;
		}
	}
	if (correct)
		cout << "CORRECT\n";
	else
	{
		cout << "WRONG\nCorrect order: \n";
		for (int i = 0; i < DAGGenerator::num_nodes; i++)
		{
			if (DAGGenerator::adj[indices[i]].size() != 0)
				cout << indices[i] << "\n";
		}
	}
}