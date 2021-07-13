#include <bits/stdc++.h>
#include "crossword_generator.h"
#include "CSPify.h"

using namespace std;

const int M=35;
vector<pair<pair<int,int>,int>> CSPify::nodes;
vector<vector<vector<int>>> CSPify::len;
vector<vector<vector<pair<int,int>>>> CSPify::edges;
vector<vector<vector<vector<pair<int,int>>>>> CSPify::graph;
vector<vector<int>> vis;
deque <pair<pair<pair<int,int>,int>,pair<pair<int,int>,int>>> CSPify::q;

void CSPify::init()
{
    len.resize(M,vector<vector<int>>(M,vector<int>(2)));
    vis.resize(M,vector<int>(M,0));
    edges.resize(M,vector<vector<pair<int,int>>>(M,vector<pair<int,int>>(2)));
    graph.resize(M,vector<vector<vector<pair<int,int>>>>(M,vector<vector<pair<int,int>>>(2)));
}

void CSPify::cspify()
{
	//Find across nodes in the grid
	for(int i=1;i<=CrosswordGenerator::grid_size+1;i++)
	{
		int ct=0;
		for(int j=1;j<=CrosswordGenerator::grid_size+1;j++)
		{
			if(CrosswordGenerator::grid[i][j]=='.')
			{
				ct++;
			}
			else
			{
				if(ct>1)
				{
					nodes.push_back({{i,j-ct},0});
					len[i][j-ct][0]=ct;
				}
				ct=0;
			}
		}
	}

	//Find down nodes in the grid
	for(int j=1;j<=CrosswordGenerator::grid_size+1;j++)
	{
		int ct=0;
		for(int i=1;i<=CrosswordGenerator::grid_size+1;i++)
		{
			if(CrosswordGenerator::grid[i][j]=='.')
			{
				ct++;
			}
			else
			{
				if(ct>1)
				{
					nodes.push_back({{i-ct,j},1});
					len[i-ct][j][1]=ct;
				}
				ct=0;
			}
		}
	}

	int m=nodes.size();

	//Find crossover points between two nodes
	for(auto cur:nodes)
	{
		int x=cur.first.first;
		int y=cur.first.second;
		int t=cur.second;

		int ty=y;
		int tx=x;
		if(t==1)
		{
			while(CrosswordGenerator::grid[tx][ty]=='.')
			{
				if(CrosswordGenerator::grid[tx][ty-1]=='.' or CrosswordGenerator::grid[tx][ty+1]=='.')
				{
					edges[tx][ty][1]={x,y};
					vis[tx][ty]=1;
				}
				tx++;
			}
		}

		if(t==0)
		{
			while(CrosswordGenerator::grid[tx][ty]=='.')
			{
				if(CrosswordGenerator::grid[tx-1][ty]=='.' or CrosswordGenerator::grid[tx+1][ty]=='.')
				{
					edges[tx][ty][0]={x,y};
					vis[tx][ty]=1;
				}
				ty++;
			}
		}

	}

	//Based on the crossover points build graph
	for(int i=1;i<CrosswordGenerator::grid_size+1;i++)
	{
		for(int j=1;j<CrosswordGenerator::grid_size+1;j++)
		{
			if(vis[i][j])
			{
				auto ph=edges[i][j][0]; //node for starting of across
				auto pv=edges[i][j][1]; //node for starting of down

				graph[ph.first][ph.second][0].push_back(pv);
				graph[pv.first][pv.second][1].push_back(ph);

				q.push_back({{{ph.first,ph.second},0},{{pv.first,pv.second},1}});
				q.push_back({{{pv.first,pv.second},1},{{ph.first,ph.second},0}});
			}
		}
	}
}



void CSPify::print_graph()
{
	cout<<"Constraint graph :\n";
	int i,j,k;
	for(auto node:nodes)
	{
		i=node.first.first;
		j=node.first.second;
		k=node.second;

		cout<<i;cout<<"-";
		cout<<j;cout<<"-";
		cout<<(k?"D":"A");cout<<"\n";
		for(auto x: graph[i][j][k])
		{
			cout<<x.first;cout<<"-";
			cout<<x.second;cout<<"-";
			cout<<(k?"A":"D")<<" ";
		}
		cout<<"\n";
	}
}
