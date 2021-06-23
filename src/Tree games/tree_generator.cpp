//generates the tree based on the parameters

#include <bits/stdc++.h>
#include "tree_generator.h"

using namespace std;

int num_vars; //number of variables
int id; //id of current node to be added
int var_name;

vector<vector<int>> adj; //stores adjacency list
vector<string> content; //stores content of each node
vector<int> values;
vector<string> operators;

//initializes the variables
void init()
{
	id=0;
	var_name='a';
	operators=vector<string>({"&","|","=>","<=>"});
	srand((unsigned)time( NULL ));
}

void generate_tree(int node,int nv)
{
	adj.push_back(vector<int>());
	if(nv==1)
	{
		if(rand()%2==1)
		{
			adj[node].push_back(++id);
			adj.push_back(vector<int>());
		}
		return;
	}
	int nv_left=rand()%(nv-1)+1;
	adj[node].push_back(++id);
	generate_tree(id,nv_left);
	adj[node].push_back(++id);	
	generate_tree(id,nv-nv_left);
}

void generate_tree() //overloaded function for calling from outside
{
	generate_tree(0,num_vars);
}

void assign_content()
{
	content.resize(adj.size());
	for(int i=0;i<adj.size();i++)
	{
		if(adj[i].size()==0)
			content[i]=var_name++;
		else if(adj[i].size()==1)
			content[i]="~";
		else
			content[i]=operators[rand()%4];
	}
}

void assign_values()
{
	values.resize(adj.size());
	for(int i=0;i<adj.size();i++){
		if(!isalpha(content[i][0]))
			continue;
		values[i]=rand()%2;
	}
}

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
	if(adj[node].size()==1)
	{
		cout<<content[node]<<content[adj[node][0]]<<" ";
		return;
	}
	cout<<"( ";
	display_expression(adj[node][0]);
	cout<<content[node]<<" ";
	display_expression(adj[node][1]);
	cout<<") ";
}

void display_expression()
{
	display_expression(0);
}

