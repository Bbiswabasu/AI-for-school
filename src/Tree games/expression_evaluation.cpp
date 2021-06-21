//Implementation of the evaluating expression game

#include <bits/stdc++.h>
#include "tree_generator.h"

using namespace std;

vector<int> values;
int answer;
void display_tree()
{
	for(int i=0;i<adj.size();i++)
	{
		cout<<i<<" "<<content[i]<<" ";
		for(auto it:adj[i])
		{
			cout<<it<<" ";
		}
		cout<<"\n";

	}
}

void display_expression(int node)
{
	if(adj[node].size()==0)
	{
		cout<<content[node]<<" ";
		return;
	}
	cout<<"( ";
	display_expression(adj[node][0]);
	cout<<content[node]<<" ";
	display_expression(adj[node][1]);
	cout<<") ";
}

int evaluate(int node)
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
	return ans;
}

int main()
{
	srand((unsigned)time( NULL ));
	int num_var=5;
	init(num_var);
	generate_tree();
	assign_content();
	display_tree();
	display_expression(0);
	cout<<"\n";

	int num_node=adj.size();
	values.resize(num_node);

	cout<<"Enter the value of given expression when :\n";
	for(int i=0;i<num_node;i++){
		if(!isalpha(content[i][0]))
			continue;
		values[i]=rand()%2;
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