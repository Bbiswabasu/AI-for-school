#include <iostream>
#include <algorithm>
#include "crossword_generator.h"
#include "find_crossword_nodes.h"
#include "CSPify.h"
using namespace std;

FindCrosswordNodes::FindCrosswordNodes() {}
vector<pair<int, int>> FindCrosswordNodes::get_nodes_across() const { return nodes_across; }
vector<pair<int, int>> FindCrosswordNodes::get_nodes_down() const { return nodes_down; }
vector<pair<pair<int, int>, char>> FindCrosswordNodes::get_missed_nodes() const { return missed_nodes; }
vector<pair<pair<int, int>, char>> FindCrosswordNodes::get_wrong_nodes() const { return wrong_nodes; }
vector<pair<pair<int, int>, char>> FindCrosswordNodes::get_correct_nodes() const { return correct_nodes; }

bool FindCrosswordNodes::check()
{
    //this is useful since CSPify::nodes follow the same structure
    //thereby making it easier to comapre the 2 vectors
    sort(nodes_across.begin(), nodes_across.end());
    sort(nodes_down.begin(), nodes_down.end(), [](pair<int, int> &a, pair<int, int> &b)
         {
             if (a.second == b.second)
                 return a.first < b.first;
             return a.second < b.second;
         });

    bool correct = 1;
    int i = 0, j = 0;
    //Check for across nodes
    while (i < CSPify::nodes.size() && j < nodes_across.size() && CSPify::nodes[i].second == 0)
    {
        pair<int, int> cur1 = CSPify::nodes[i].first, cur2 = nodes_across[j];
        if (cur1.first < cur2.first || (cur1.first == cur2.first && cur1.second < cur2.second))
        {
            missed_nodes.push_back({{cur1.first, cur1.second}, 'A'});
            i++;
            correct = 0;
        }
        else if (cur2.first < cur1.first || (cur2.first == cur1.first && cur2.second < cur1.second))
        {
            wrong_nodes.push_back({{cur2.first, cur2.second}, 'A'});
            j++;
            correct = 0;
        }
        else
        {
            correct_nodes.push_back({{cur1.first, cur1.second}, 'A'});
            i++;
            j++;
        }
    }
    while (i < CSPify::nodes.size() && CSPify::nodes[i].second == 0)
    {
        pair<int, int> cur1 = CSPify::nodes[i].first;
        missed_nodes.push_back({{cur1.first, cur1.second}, 'A'});
        i++;
        correct = 0;
    }
    while (j < nodes_across.size())
    {
        pair<int, int> cur2 = nodes_across[j];
        wrong_nodes.push_back({{cur2.first, cur2.second}, 'A'});
        j++;
        correct = 0;
    }

    //Check for down nodes
    j = 0;
    while (i < CSPify::nodes.size() && j < nodes_down.size())
    {
        pair<int, int> cur1 = CSPify::nodes[i].first, cur2 = nodes_down[j];
        if (cur1.second < cur2.second || (cur1.second == cur2.second && cur1.first < cur2.first))
        {
            missed_nodes.push_back({{cur1.first, cur1.second}, 'D'});
            i++;
            correct = 0;
        }
        else if (cur2.second < cur1.second || (cur2.second == cur1.second && cur2.first < cur1.first))
        {
            wrong_nodes.push_back({{cur2.first, cur2.second}, 'D'});
            j++;
            correct = 0;
        }
        else
        {
            correct_nodes.push_back({{cur1.first, cur1.second}, 'D'});
            i++;
            j++;
        }
    }
    while (i < CSPify::nodes.size())
    {
        pair<int, int> cur1 = CSPify::nodes[i].first;
        missed_nodes.push_back({{cur1.first, cur1.second}, 'D'});
        i++;
        correct = 0;
    }
    while (j < nodes_down.size())
    {
        pair<int, int> cur2 = nodes_down[j];
        wrong_nodes.push_back({{cur2.first, cur2.second}, 'D'});
        j++;
        correct = 0;
    }
    return correct;
}
void FindCrosswordNodes::display_result()
{
    bool correct = check();
    for (auto node : correct_nodes)
        cout << "You marked correctly : " << node.first.first << "-" << node.first.second << "-" << node.second << "\n";
    for (auto node : wrong_nodes)
        cout << "You marked wrong : " << node.first.first << "-" << node.first.second << "-" << node.second << "\n";
    for (auto node : missed_nodes)
        cout << "You missed : " << node.first.first << "-" << node.first.second << "-" << node.second << "\n";

    if (correct)
        cout << "ALL ARE CORRECT\n";
}
void FindCrosswordNodes::add_node(int x, int y, char dir)
{
    if (dir == 'A')
        nodes_across.push_back({x, y});
    if (dir == 'D')
        nodes_down.push_back({x, y});
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
        add_node(x, y, dir[0]);
    }
    display_result();
}