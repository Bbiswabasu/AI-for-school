#include <bits/stdc++.h>
#include "crossword_backtracking_tree.h"
#include "crossword_generator.h"
#include "CSPify.h"
#include "arc_consistency.h"
using namespace std;

const int M = 35;
ArcConsistency arc_con;
void CrosswordBacktrackingTree::backtrack(int node)
{
    arc_con.ac3();
    node_id++;
    int my_id=node_id;
    grid_state.push_back(CrosswordGenerator::grid);
    adj.push_back(vector<int>());
    domain_state.push_back(arc_con.domain);
    if (node == CSPify::nodes.size())
        return;
    int x = CSPify::nodes[node].first.first, y = CSPify::nodes[node].first.second, dir = CSPify::nodes[node].second;
    int length = CSPify::len[x][y][dir];
    vector<int> empty_spots;                           //stores which spots in crossword are empty
    vector<pair<pair<int, int>, int>> removed_current; //stores nodes from which current word got removed
    vector<int> removed_domain;                        //stores which words were removed from nodes domain
    for (int i = 0; i < length; i++)
    {
        if (CrosswordGenerator::grid[x + dir * i][y + (1 - dir) * i] == '.')
            empty_spots.push_back(i);
    }
    for (int i = 0; i < arc_con.szbag; i++)
    {
        if (arc_con.domain[x][y][dir][i])
        {
            //fill this node with i-th word
            int tx = x, ty = y;
            for (int pos = 0; pos < CSPify::len[x][y][dir]; pos++)
            {
                CrosswordGenerator::grid[tx][ty] = CrosswordGenerator::bag[length][arc_con.rebag[length][i]][pos];
                if (dir == 0)
                    ty++;
                else
                    tx++;
            }
            //remove this word from all other nodes
            for (auto it : CSPify::nodes)
            {
                int sx = it.first.first, sy = it.first.second, sdir = it.second;
                if (sx == x && sy == y && sdir == dir)
                    continue;
                if (CSPify::len[sx][sy][sdir] == length && arc_con.domain[sx][sy][sdir][i])
                {
                    arc_con.domain[sx][sy][sdir][i] = 0;
                    removed_current.push_back(it);
                }
            }
            //remove all words from domain of node
            for (int j = 0; j < arc_con.szbag; j++)
            {
                if (i != j && arc_con.domain[x][y][dir][j])
                {
                    arc_con.domain[x][y][dir][j] = 0;
                    removed_domain.push_back(j);
                }
            }
            adj[my_id].push_back(node_id + 1);
            backtrack(node + 1);
            //revert back to original state
            for (auto pos : empty_spots)
            {
                CrosswordGenerator::grid[x + (1 - dir) * pos][y + dir * pos] = '.';
            }
            for (auto it : removed_current)
            {
                int sx = it.first.first, sy = it.first.second, sdir = it.second;
                arc_con.domain[sx][sy][sdir][i] = 1;
            }
            for (auto it : removed_domain)
            {
                arc_con.domain[x][y][dir][it] = 1;
            }
        }
    }
}
void CrosswordBacktrackingTree::startGame()
{
    node_id = -1;
    cout << "Enter bag size : ";
    cin >> arc_con.szbag;
    arc_con.init();
    arc_con.choose();
    backtrack(0);
    cout << "Adjacency list of recursion tree :\n";
    for (int i = 0; i < adj.size(); i++)
    {
        cout << i << " --> ";
        for (auto it : adj[i])
            cout << it << " ";
        cout << "\n";
    }
    while (1)
    {
        int n;
        cout << "Enter node to see state : ";
        cin >> n;
        if (n >= adj.size())
            break;
        cout << "Crossword state :\n";
        for (int i = 1; i <= CrosswordGenerator::grid_size; i++)
        {
            for (int j = 1; j <= CrosswordGenerator::grid_size; j++)
            {
                cout << grid_state[n][i][j] << " ";
            }
            cout << "\n";
        }
        cout<<"\nDomain state :\n";
        arc_con.domain = domain_state[n];
        arc_con.print_bag();
    }
}