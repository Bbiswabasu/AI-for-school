//Implementation of the evaluating expression game

#include <bits/stdc++.h>
#include "dag_generator.h"
#include "expression_evaluation.h"
#include "match_expression_with_node.h"

using namespace std;

int answer;

ExpressionEvaluation::ExpressionEvaluation()
{
	done.resize(DAGGenerator::adj.size(),0);
}

int ExpressionEvaluation::evaluate(int node)
{
	if(done[node])
		return DAGGenerator::values[node];
	if(DAGGenerator::adj[node].size()==0)
	{
		cout<<node<<" -> "<<DAGGenerator::values[node]<<"\n";
		done[node]=1;
		return DAGGenerator::values[node];
	}
	int ans;
	if(DAGGenerator::adj[node].size()==1)
	{
		ans=!(evaluate(DAGGenerator::adj[node][0]));
		cout<<node<<" -> "<<ans<<"\n";
		done[node]=1;
		return ans;
	}
	int left=evaluate(DAGGenerator::adj[node][0]);
	int right=evaluate(DAGGenerator::adj[node][1]);
	if(DAGGenerator::content[node]=="&")
		ans=left&right;
	else if(DAGGenerator::content[node]=="|")
		ans=left|right;
	else if(DAGGenerator::content[node]=="=>")
		ans=(!left)|right;
	else if(DAGGenerator::content[node]=="<=>")
		ans=((!left)&(!right))|(left&right);
	cout<<node<<" -> "<<ans<<"\n";
	DAGGenerator::values[node]=ans;
	done[node]=1;
	return ans;
}

void ExpressionEvaluation::startGame()
{
	MatchExpression mat;
	mat.compute_expressions(0);
	cout<<DAGGenerator::expressions[0]<<"\n";

	int num_node=DAGGenerator::adj.size();
	cout<<"Enter the value of given expression when :\n";
	for(int i=0;i<num_node;i++){
		if(DAGGenerator::adj[i].size()==0)
			cout<<DAGGenerator::content[i]<<" = "<<DAGGenerator::values[i]<<", ";
	}
	cout<<"\n";
	
	int user_value;
	cin>>user_value;
	answer=evaluate(0);
	if(user_value==answer)
		cout<<"CORRECT\n";
	else
		cout<<"WRONG\n";
}