#include <iostream>
#include <algorithm>
#include "crossword_generator.h"
#include "draw_crossword_graph.h"
#include "CSPify.h"
using namespace std;

const int M = 35;
DrawCrosswordGraph::DrawCrosswordGraph() {}
vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> DrawCrosswordGraph::get_missed_edges() const { return missed_edges; }
vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> DrawCrosswordGraph::get_wrong_edges() const { return wrong_edges; }
vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> DrawCrosswordGraph::get_correct_edges() const { return correct_edges; }

void DrawCrosswordGraph::init()
{
    graph.resize(M, vector<vector<vector<pair<int, int>>>>(M, vector<vector<pair<int, int>>>(2)));
}

bool DrawCrosswordGraph::check()
{
    bool correct = 1;
    for (auto node : CSPify::nodes)
    {
        if (node.second == 1)
            break;
        int fx = node.first.first, fy = node.first.second, fdir = node.second;
        sort(graph[fx][fy][fdir].begin(), graph[fx][fy][fdir].end(), [](pair<int, int> &a, pair<int, int> &b)
             {
                 if (a.second == b.second)
                     return a.first < b.first;
                 return a.second < b.second;
             });
        int i = 0, j = 0;
        while (i < CSPify::graph[fx][fy][fdir].size() && j < graph[fx][fy][fdir].size())
        {
            int x1 = CSPify::graph[fx][fy][fdir][i].first, y1 = CSPify::graph[fx][fy][fdir][i].second;
            int x2 = graph[fx][fy][fdir][j].first, y2 = graph[fx][fy][fdir][j].second;
            if (y1 < y2)
            {
                missed_edges.push_back({{{fx, fy}, 'A'}, {{x1, y1}, 'D'}});
                i++;
                correct = 0;
            }
            else if (y1 > y2)
            {
                wrong_edges.push_back({{{fx, fy}, 'A'}, {{x2, y2}, 'D'}});
                j++;
                correct = 0;
            }
            else
            {
                if (x1 == x2)
                {
                    correct_edges.push_back({{{fx, fy}, 'A'}, {{x2, y2}, 'D'}});
                    i++;
                    j++;
                }
                else
                {
                    if (x1 < x2)
                    {
                        missed_edges.push_back({{{fx, fy}, 'A'}, {{x1, y1}, 'D'}});
                        i++;
                        correct = 0;
                    }
                    else
                    {
                        wrong_edges.push_back({{{fx, fy}, 'A'}, {{x2, y2}, 'D'}});
                        j++;
                        correct = 0;
                    }
                }
            }
        }
        while (i < CSPify::graph[fx][fy][fdir].size())
        {
            int x1 = CSPify::graph[fx][fy][fdir][i].first, y1 = CSPify::graph[fx][fy][fdir][i].second;
            missed_edges.push_back({{{fx, fy}, 'A'}, {{x1, y1}, 'D'}});
            i++;
            correct = 0;
        }
        while (j < graph[fx][fy][fdir].size())
        {
            int x2 = graph[fx][fy][fdir][j].first, y2 = graph[fx][fy][fdir][j].second;
            wrong_edges.push_back({{{fx, fy}, 'A'}, {{x2, y2}, 'D'}});
            j++;
            correct = 0;
        }
    }
    return correct;
}

void DrawCrosswordGraph::display_result()
{
    bool correct = check();
    for (auto edge : correct_edges)
    {
        auto node1 = edge.first, node2 = edge.second;
        cout << "You marked correctly : " << node1.first.first << "-" << node1.first.second << "-" << node1.second << " --> " << node2.first.first << "-" << node2.first.second << "-" << node2.second << "\n";
    }
    for (auto edge : wrong_edges)
    {
        auto node1 = edge.first, node2 = edge.second;
        cout << "You marked wrong : " << node1.first.first << "-" << node1.first.second << "-" << node1.second << " --> " << node2.first.first << "-" << node2.first.second << "-" << node2.second << "\n";
    }
    for (auto edge : missed_edges)
    {
        auto node1 = edge.first, node2 = edge.second;
        cout << "You missed : " << node1.first.first << "-" << node1.first.second << "-" << node1.second << " --> " << node2.first.first << "-" << node2.first.second << "-" << node2.second << "\n";
    }

    if (correct)
        cout << "ALL ARE CORRECT\n";
}

void DrawCrosswordGraph::add_edge(int fx, int fy, int fdir, int sx, int sy, int sdir)
{
    //maintain adjacency list of only across nodes as they are sorted by y coordinate

    if (fdir == 'A')
        fdir = 0;
    else
        fdir = 1;

    if (sdir == 'A')
        sdir = 0;
    else
        sdir = 1;

    if (sdir == 0)
    {
        swap(fx, sx);
        swap(fy, sy);
        swap(fdir, sdir);
    }

    graph[fx][fy][fdir].push_back({sx, sy});
}
void DrawCrosswordGraph::startGame()
{
    cout << "Nodes of the graph are :\n";

    //display across nodes
    int i = 0;
    for (; i < CSPify::nodes.size(); i++)
    {
        pair<pair<int, int>, int> node = CSPify::nodes[i];
        if (node.second == 1)
            break;
        cout << node.first.first << "-" << node.first.second << "-A     ";
    }
    cout << "\n";
    //display down nodes
    for (; i < CSPify::nodes.size(); i++)
    {
        pair<pair<int, int>, int> node = CSPify::nodes[i];
        cout << node.first.first << "-" << node.first.second << "-D     ";
    }
    cout << "\n";

    init();
    cout << "Find all edges between 'A' & 'D' nodes (put 0 to stop) :\n";

    //take input of graph
    while (1)
    {
        int fx, fy, sx, sy;
        string fdir, sdir;
        cin >> fx;
        if (fx == 0)
            break;
        cin >> fy >> fdir >> sx >> sy >> sdir;
        add_edge(fx, fy, fdir[0], sx, sy, sdir[0]);
    }
    display_result();
}