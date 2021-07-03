//Implementation of the match expression with node game

#include <bits/stdc++.h>
#include "dag_generator.h"
#include "match_expression_with_node.h"

using namespace std;

vector<pair<string,int>> exp_node;

MatchExpression::MatchExpression()
{
	done.resize(adj.size(),0);
}
string MatchExpression::compute_expressions(int node)
{
	if(done[node])
		return expressions[node];
	if(adj[node].size()==0)
	{
		done[node]=1;
		return expressions[node]=content[node];
	}
	if(adj[node].size()==1)
	{
		expressions[node]="( ~ "+compute_expressions(adj[node][0])+" )";
		done[node]=1;
		return expressions[node];
	}
	string ans="( ";
	ans+=compute_expressions(adj[node][0])+" ";
	ans+=content[node]+" ";
	ans+=compute_expressions(adj[node][1])+" ";
	ans+=")";
	expressions[node]=ans;
	done[node]=1;
	return ans;
}

void MatchExpression::startGame()
{
	compute_expressions(0);
	exp_node.resize(num_nodes);

	for(int i=0;i<num_nodes;i++)
		exp_node[i]={expressions[i],i};
	random_shuffle(exp_node.begin(),exp_node.end()); //Shuffle the list of expressions
	
	for(int i=0;i<num_nodes;i++)
	{
		if(adj[exp_node[i].second].size()!=0)
			cout<<exp_node[i].first<<"\n";
	}

	cout<<"Match each expression with corresponding node number : \n";
	bool correct=1;
	for(int i=0;i<num_nodes;i++)
	{
		if(adj[exp_node[i].second].size()==0)
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
		for(int i=0;i<num_nodes;i++)
		{
			if(adj[exp_node[i].second].size()!=0)
				cout<<exp_node[i].second<<"\n";
		}
	}
}