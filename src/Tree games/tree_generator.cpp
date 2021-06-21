//generates the tree based on the parameters

#include <bits/stdc++.h>
#include "tree_generator.h"

using namespace std;

int num_vars; //number of variables
int id; //id of current node to be added
int var_name;

vector<vector<int>> adj; //stores adjacency list
vector<string> content; //stores content of each node
vector<string> operators;

//initializes the variables
void init(int nv)
{
	num_vars=nv;
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

void assign_content(int node)
{
	if(adj[node].size()==0)
	{
		
		content[node]=var_name;
		var_name++;
		return;
	}
	content[node]=operators[rand()%4];
	assign_content(adj[node][0]);
	assign_content(adj[node][1]);
}
void assign_content()
{
	content.resize(adj.size());
	assign_content(0);
}
