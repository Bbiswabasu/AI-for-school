//Implementation of the evaluating expression game

#include <bits/stdc++.h>
#include "tree_generator.h"
#include "expression_evaluation.h"

using namespace std;

int answer;

int ExpressionEvaluation::evaluate(int node)
{
	if(adj[node].size()==0)
	{
		cout<<node<<" -> "<<values[node]<<"\n";
		return values[node];
	}
	int left=evaluate(adj[node][0]);
	int right=evaluate(adj[node][1]);
	int ans;
	if(content[node]=="&")
		ans=left&right;
	else if(content[node]=="|")
		ans=left|right;
	else if(content[node]=="=>")
		ans=(!left)|right;
	else if(content[node]=="<=>")
		ans=((!left)&(!right))|(left&right);
	cout<<node<<" -> "<<ans<<"\n";
	values[node]=ans;
	return ans;
}

void ExpressionEvaluation::startGame()
{
	display_expression();
	cout<<"\n";

	int num_node=adj.size();
	cout<<"Enter the value of given expression when :\n";
	for(int i=0;i<num_node;i++){
		if(adj[i].size()==0)
			cout<<content[i]<<" = "<<values[i]<<", ";
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