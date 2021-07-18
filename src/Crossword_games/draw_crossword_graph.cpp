#include <bits/stdc++.h>
#include "crossword_generator.h"
#include "draw_crossword_graph.h"
#include "CSPify.h"
using namespace std;

void DrawCrosswordGraph::startGame()
{
    cout<<"Nodes of the graph are :\n";

    //display across nodes
    int i=0;
    for(;i<CSPify::nodes.size();i++)
    {
        pair<pair<int,int>,int> node=CSPify::nodes[i];
        if(node.second==1)
            break;
        cout<<node.first.first<<"-"<<node.first.second<<"-A     ";
    }
    cout<<"\n";
    //display down nodes
    for(;i<CSPify::nodes.size();i++)
    {
        pair<pair<int,int>,int> node=CSPify::nodes[i];
        cout<<node.first.first<<"-"<<node.first.second<<"-D     ";
    }
    cout<<"\n";
    cout<<"Find all edges between 'A' & 'D' nodes :\n";
}