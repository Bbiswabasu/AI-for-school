#include <bits/stdc++.h>
#include "crossword_generator.h"
#include "draw_crossword_graph.h"
#include "CSPify.h"
using namespace std;

const int M=35;

void DrawCrosswordGraph::check()
{
    //take input of graph
    while(1)
    {
        int fx;
        cin>>fx;
        if(fx==0)
            break;

        int fy,fdir,sx,sy,sdir;
        string dir;
        cin>>fy>>dir;
        if(dir=="A")
            fdir=0;
        else
            fdir=1;

        cin>>sx>>sy>>dir;
        if(dir=="A")
            sdir=0;
        else
            sdir=1;
        
        //maintain adjacency list of only across nodes as they are sorted by y coordinate
        if(sdir==0)
        {
            swap(fx,sx);
            swap(fy,sy);
            swap(fdir,sdir);
        }
        graph[fx][fy][fdir].push_back({sx,sy});
    }
    for(auto node:CSPify::nodes)
    {
        if(node.second==1)
            break;
        int fx=node.first.first, fy=node.first.second, fdir=node.second;
        sort(graph[fx][fy][fdir].begin(),graph[fx][fy][fdir].end(),[](pair<int,int> &a,pair<int,int> &b)
        {
            if(a.second==b.second)
                return a.first<b.first;
            return a.second<b.second;
        });
        int i=0,j=0;
        while(i<CSPify::graph[fx][fy][fdir].size() && j<graph[fx][fy][fdir].size())
        {
            int x1=CSPify::graph[fx][fy][fdir][i].first, y1=CSPify::graph[fx][fy][fdir][i].second;
            int x2=graph[fx][fy][fdir][j].first, y2=graph[fx][fy][fdir][j].second;
            if(y1<y2)
            {
                cout<<"You missed edge : "<<fx<<"-"<<fy<<"-A --> "<<x1<<"-"<<y1<<"-D\n";
                i++;
            }
            else if(y1>y2)
            {
                cout<<"You chose wrong edge : "<<fx<<"-"<<fy<<"-A --> "<<x2<<"-"<<y2<<"-D\n";
                j++;
            }
            else
            {
                if(x1==x2)
                {
                    cout<<"You marked correctly : "<<fx<<"-"<<fy<<"-A --> "<<x2<<"-"<<y2<<"-D\n";
                    i++; j++;
                }
                else
                {
                    if(x1<x2)
                    {
                        cout<<"You missed edge : "<<fx<<"-"<<fy<<"-A --> "<<x1<<"-"<<y1<<"-D\n";
                        i++;
                    }
                    else
                    {
                        cout<<"You chose wrong edge : "<<fx<<"-"<<fy<<"-A --> "<<x2<<"-"<<y2<<"-D\n";
                        j++;
                    }
                }
            }
        }
        while(i<CSPify::graph[fx][fy][fdir].size())
        {
            int x1=CSPify::graph[fx][fy][fdir][i].first, y1=CSPify::graph[fx][fy][fdir][i].second;
            cout<<"You missed edge : "<<fx<<"-"<<fy<<"-A --> "<<x1<<"-"<<y1<<"-D\n";
            i++;
        }
        while(j<graph[fx][fy][fdir].size())
        {
            int x2=graph[fx][fy][fdir][j].first, y2=graph[fx][fy][fdir][j].second;
            cout<<"You chose wrong edge : "<<fx<<"-"<<fy<<"-A --> "<<x2<<"-"<<y2<<"-D\n";
            j++;
        }
    }
}

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
    cout<<"Find all edges between 'A' & 'D' nodes (put 0 to stop) :\n";
    graph.resize(M,vector<vector<vector<pair<int,int>>>>(M,vector<vector<pair<int,int>>>(2)));
    check();
}