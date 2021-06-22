//Implementation of the match expression with node game

#include <bits/stdc++.h>
#include "tree_generator.h"
#include "match_expression_with_node.h"

using namespace std;

vector<pair<string,int>> expressions;

string MatchExpression::compute_expressions(int node)
{
	if(adj[node].size()==0)
	{
		expressions[node]={content[node],node};
		return content[node];
	}
	string ans="( ";
	ans+=compute_expressions(adj[node][0])+" ";
	ans+=content[node]+" ";
	ans+=compute_expressions(adj[node][1])+" ";
	ans+=") ";
	expressions[node]={ans,node};
	return ans;
}

void MatchExpression::startGame()
{
	int num_node=adj.size();
	expressions.resize(num_node);
	compute_expressions(0);
	random_shuffle(expressions.begin(),expressions.end());
	
	for(int i=0;i<num_node;i++)
	{
		if(adj[expressions[i].second].size()!=0)
			cout<<expressions[i].first<<"\n";
	}

	cout<<"Match each expression with corresponding node number : \n";
	bool correct=1;
	for(int i=0;i<num_node;i++)
	{
		if(adj[expressions[i].second].size()==0)
			continue;
		int n;
		cin>>n;
		if(n!=expressions[i].second){
			correct=0;
			break;
		}
	}
	if(correct)
		cout<<"CORRECT\n";
	else{
		cout<<"WRONG\nCorrect order: \n";
		for(int i=0;i<num_node;i++)
		{
			if(adj[expressions[i].second].size()!=0)
				cout<<expressions[i].second<<"\n";
		}
	}
}