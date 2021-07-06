//Implementation of the match expression with node game

#include <bits/stdc++.h>
#include "dag_generator.h"
#include "match_expression_with_node.h"

using namespace std;

vector<pair<string,int>> exp_node;

MatchExpression::MatchExpression()
{
	done.resize(DAGGenerator::adj.size(),0);
}
string MatchExpression::compute_expressions(int node)
{
	if(done[node])
		return DAGGenerator::expressions[node];
	if(DAGGenerator::adj[node].size()==0)
	{
		done[node]=1;
		return DAGGenerator::expressions[node]=DAGGenerator::content[node];
	}
	if(DAGGenerator::adj[node].size()==1)
	{
		DAGGenerator::expressions[node]="( ~ "+compute_expressions(DAGGenerator::adj[node][0])+" )";
		done[node]=1;
		return DAGGenerator::expressions[node];
	}
	string ans="( ";
	ans+=compute_expressions(DAGGenerator::adj[node][0])+" ";
	ans+=DAGGenerator::content[node]+" ";
	ans+=compute_expressions(DAGGenerator::adj[node][1])+" ";
	ans+=")";
	DAGGenerator::expressions[node]=ans;
	done[node]=1;
	return ans;
}

void MatchExpression::startGame()
{
	compute_expressions(0);
	exp_node.resize(DAGGenerator::num_nodes);

	for(int i=0;i<DAGGenerator::num_nodes;i++)
		exp_node[i]={DAGGenerator::expressions[i],i};
	random_shuffle(exp_node.begin(),exp_node.end()); //Shuffle the list of DAGGenerator::expressions
	
	for(int i=0;i<DAGGenerator::num_nodes;i++)
	{
		if(DAGGenerator::adj[exp_node[i].second].size()!=0)
			cout<<exp_node[i].first<<"\n";
	}

	cout<<"Match each expression with corresponding node number : \n";
	bool correct=1;
	for(int i=0;i<DAGGenerator::num_nodes;i++)
	{
		if(DAGGenerator::adj[exp_node[i].second].size()==0)
			continue;
		int n;
		cin>>n;
		if(n!=exp_node[i].second){
			correct=0;
		}
	}
	if(correct)
		cout<<"CORRECT\n";
	else{
		cout<<"WRONG\nCorrect order: \n";
		for(int i=0;i<DAGGenerator::num_nodes;i++)
		{
			if(DAGGenerator::adj[exp_node[i].second].size()!=0)
				cout<<exp_node[i].second<<"\n";
		}
	}
}