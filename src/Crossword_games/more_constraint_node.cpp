#include <bits/stdc++.h>
#include "find_missing_arc.h"
#include "crossword_generator.h"
#include "CSPify.h"
#include "more_constraint_node.h"
using namespace std;

int x,y,t;
void MoreConstraintNode::fiilv1()
{
	int numofnodes=CSPify::nodes.size();
	int temp=rand()%numofnodes;
	auto cur=CSPify::nodes[temp];

    x=cur.first.first;
    y=cur.first.second;
    t=cur.second;

	int ct=CSPify::len[x][y][t];
	string s=CrosswordGenerator::bag[ct][rand()%30];
	if(t==0)
	{
		for(int i=0;i<ct;i++)
		{
			CrosswordGenerator::grid[x][y+i]=s[i];
		}
	}
	else
	{
		for(int i=0;i<ct;i++)
		{
			CrosswordGenerator::grid[x+i][y]=s[i];
		}
	}
	
}

void MoreConstraintNode::empty_grid()
{
    for(int i=1;i<=CrosswordGenerator::grid_size;i++)
    {
        for(int j=1;j<=CrosswordGenerator::grid_size;j++)
        {
            if(CrosswordGenerator::grid[i][j]!='#')
                CrosswordGenerator::grid[i][j]='.';
        }
    }
}

void MoreConstraintNode::startGame()
{
	cout<<"What all nodes are more constrained than others?\n";
    fiilv1();
    CrosswordGenerator cross_gen;
    cross_gen.print_grid();
    cout<<"Ans:\n";
	for(auto cur:CSPify::graph[x][y][t])
	{
		cout<<cur.first;cout<<"-";
		cout<<cur.second;cout<<" ";;
		cout<<"\n";
	}

    empty_grid();
}