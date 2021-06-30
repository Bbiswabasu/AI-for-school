#include <bits/stdc++.h>
#include "dag_generator.h"
using namespace std;

int num_vars; //number of variables
int num_nodes;
int id; //id of current node to be added
int var_name;

vector<vector<int>> adj; //stores adjacency list
vector<string> content; //stores content of each node
vector<int> values; //stores values at each node
vector<string> operators; //stores list of operators
vector<int> indeg; //stores indegree of each node

void init()
{
	id=0;
	var_name='a';
	operators=vector<string>({"&","|","=>","<=>"});
	srand((unsigned)time( NULL ));
}
int random(int a,int b)
{
	return a+rand()%(b-a+1);
}
void generate_dag()
{
	int num_not=random(0,num_vars); //numbers of NOT nodes to be inserted

	num_nodes+=num_not;
	adj.resize(num_nodes,vector<int>());
	indeg.resize(num_nodes,0);
	num_nodes-=num_not;

	//Randomly connect nodes following topological order
	for(int i=0;i<num_nodes-num_vars;i++)
	{
		int succ1;
		if(indeg[i+1]==0) // to ensure non-sink nodes have indegree>=1
			succ1=i+1;
		else
			succ1=random(i+1,num_nodes-1);
		int succ2;
		if(succ1!=i+1)
			succ2=random(i+1,succ1-1);
		else
			succ2=random(succ1+1,num_nodes-1);
		adj[i].push_back(succ1);
		adj[i].push_back(succ2);
		indeg[succ1]++; indeg[succ2]++;
	}

	//Ensure sink nodes have indegree>=1 
	int i=0,j=num_nodes-num_vars;
	while(j<num_nodes)
	{
		if(indeg[j]>=1)
		{
			j++;
			continue;
		}
		if(indeg[adj[i][0]]>1)
		{
			indeg[adj[i][0]]--;
			int succ2=adj[i][1];
			adj[i].pop_back(); adj[i].pop_back();
			adj[i].push_back(j);
			adj[i].push_back(succ2);
			indeg[j]++;
			j++;
		}
		else if(indeg[adj[i][1]]>1)
		{
			indeg[adj[i][1]]--;
			adj[i].pop_back();
			adj[i].push_back(j);
			indeg[j]++;
			j++;
		}
		else
			i++;
	}

	//Add NOT nodes in between
	num_nodes+=num_not;
	for(int i=num_nodes-1;i>=num_nodes-num_not;i--)
	{
		int index=random(0,num_nodes-num_not-num_vars-1);
		adj[i].push_back(adj[index][1]);
		adj[index].pop_back();
		adj[index].push_back(i);
	}
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

void display_dag()
{
	cout<<"Adjacency list and content of each node :\n";
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
		cout<<"( ";
		cout<<content[node]<<" ";
		display_expression(adj[node][0]);
		cout<<") ";
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