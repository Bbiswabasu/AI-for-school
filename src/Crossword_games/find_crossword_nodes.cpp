#include <iostream>
#include <algorithm>
#include "crossword_generator.h"
#include "find_crossword_nodes.h"
#include "CSPify.h"
using namespace std;

void FindCrosswordNodes::check()
{
    //this is useful since CSPify::nodes follow the same structure
    //thereby making it easier to comapre the 2 vectors
    sort(nodes_across.begin(), nodes_across.end());
    sort(nodes_down.begin(), nodes_down.end(), [](pair<int, int> &a, pair<int, int> &b)
         {
             if (a.second == b.second)
                 return a.first < b.first;
            return a.second<b.second;
             
         });
    
    bool correct=1;
    int i=0,j=0;
    //Check for across nodes
    while(i<CSPify::nodes.size() && j<nodes_across.size() && CSPify::nodes[i].second==0)
    {
        pair<int,int> cur1=CSPify::nodes[i].first, cur2=nodes_across[j];
        if(cur1.first<cur2.first || (cur1.first==cur2.first && cur1.second<cur2.second))
        {
            cout<<"You missed the node : "<<cur1.first<<"-"<<cur1.second<<"-A\n";
            i++;
            correct=0;
        }
        else if(cur2.first<cur1.first || (cur2.first==cur1.first && cur2.second<cur1.second))
        {
            cout<<"You chose wrong node : "<<cur2.first<<"-"<<cur2.second<<"-A\n";
            j++;
            correct=0;
        }
        else
        {
            cout<<"You marked correctly : "<<cur1.first<<"-"<<cur2.second<<"-A\n";
            i++;j++;
        }
    }
    while(i<CSPify::nodes.size() && CSPify::nodes[i].second==0)
    {
        pair<int,int> cur1=CSPify::nodes[i].first;
        cout<<"You missed the node : "<<cur1.first<<"-"<<cur1.second<<"-A\n";
        i++;
        correct=0;
    }
    while(j<nodes_across.size())
    {
        pair<int,int> cur2=nodes_across[j];
        cout<<"You chose wrong node : "<<cur2.first<<"-"<<cur2.second<<"-A\n";
        j++;
        correct=0;
    }

    //Check for down nodes
    j=0;
    while(i<CSPify::nodes.size() && j<nodes_down.size())
    {
        pair<int,int> cur1=CSPify::nodes[i].first, cur2=nodes_down[j];
        if(cur1.second<cur2.second || (cur1.second==cur2.second && cur1.first<cur2.first))
        {
            cout<<"You missed the node : "<<cur1.first<<"-"<<cur1.second<<"-D\n";
            i++;
            correct=0;
        }
        else if(cur2.second<cur1.second || (cur2.second==cur1.second && cur2.first<cur1.first))
        {
            cout<<"You chose wrong node : "<<cur2.first<<"-"<<cur2.second<<"-D\n";
            j++;
            correct=0;
        }
        else
        {
            cout<<"You marked correctly : "<<cur1.first<<"-"<<cur2.second<<"-D\n";
            i++;j++;
        }
    }
    while(i<CSPify::nodes.size())
    {
        pair<int,int> cur1=CSPify::nodes[i].first;
        cout<<"You missed the node : "<<cur1.first<<"-"<<cur1.second<<"-D\n";
        i++;
        correct=0;
    }
    while(j<nodes_down.size())
    {
        pair<int,int> cur2=nodes_down[j];
        cout<<"You chose wrong node : "<<cur2.first<<"-"<<cur2.second<<"-D\n";
        j++;
        correct=0;
    }
    if(correct)
        cout<<"ALL ARE CORRECT\n";
}
void FindCrosswordNodes::startGame()
{
    cout << "Find all nodes in the grid (x y direction) and write 0 to stop :\n";
    while (1)
    {
        int x, y;
        string dir;
        cin >> x;
        if (x == 0)
        {
            break;
        }
        cin >> y >> dir;
        if (dir == "A")
            nodes_across.push_back({x, y});
        if (dir == "D")
            nodes_down.push_back({x, y});
    }
    check();
}