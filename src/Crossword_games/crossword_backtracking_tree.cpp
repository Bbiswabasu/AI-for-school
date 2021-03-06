#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <queue>
#include "crossword_backtracking_tree.h"
#include "crossword_generator.h"
#include "CSPify.h"
using namespace std;

const int M = 35;

CrosswordBacktrackingTree::CrosswordBacktrackingTree() {}
int CrosswordBacktrackingTree::get_max_depth() const { return max_depth; }
void CrosswordBacktrackingTree::set_max_depth(int x) { max_depth = x; }
int CrosswordBacktrackingTree::get_max_nodes() const { return max_nodes; }
void CrosswordBacktrackingTree::set_max_nodes(int x) { max_nodes = x; }
int CrosswordBacktrackingTree::get_bag_size() const { return bag_size; }
void CrosswordBacktrackingTree::set_bag_size(int x) { bag_size = x; }
vector<vector<int>> CrosswordBacktrackingTree::get_adj() const { return adj; }
vector<vector<vector<char>>> CrosswordBacktrackingTree::get_grid_state() const { return grid_state; }
vector<int> CrosswordBacktrackingTree::get_result() const { return result; }
vector<int> CrosswordBacktrackingTree::get_order() const { return order; }

void CrosswordBacktrackingTree::restore_grid_state(int i, int j, int k, char ch)
{
    if (grid_state.size() <= i)
        grid_state.push_back(vector<vector<char>>());
    if (grid_state[i].size() <= j)
        grid_state[i].push_back(vector<char>());
    grid_state[i][j].push_back(ch);
}
void CrosswordBacktrackingTree::restore_adj(int a, int b)
{
    if (adj.size() <= a)
        adj.push_back(vector<int>());
    adj[a].push_back(b);
}
void CrosswordBacktrackingTree::backtrack(int node, int depth)
{
    if (depth == max_depth + 1 || node_id == max_nodes + 1)
        return;
    // arc_con.ac3();
    // ArcConsistency temp_obj = arc_con; //to revert it back to intial state after backtracking

    // domain_state.push_back(arc_con.domain);

    int my_id = node_id;

    if (node == CSPify::nodes.size())
    {
        // solution_indices.push_back(node_id);
        return;
    }
    int x = CSPify::nodes[reordered_nodes[node]].first.first, y = CSPify::nodes[reordered_nodes[node]].first.second, dir = CSPify::nodes[reordered_nodes[node]].second;
    int length = CSPify::len[x][y][dir];

    vector<int> empty_spots;                           // stores which spots in crossword are empty
    vector<pair<pair<int, int>, int>> removed_current; // stores nodes from which current word got removed
    vector<int> removed_domain;                        // stores which words were removed from nodes domain
    for (int i = 0; i < length; i++)
    {
        if (CrosswordGenerator::grid[x + dir * i][y + (1 - dir) * i] == '.')
            empty_spots.push_back(i);
    }

    for (int i = 0; i < arc_con.bag_size; i++)
    {
        if (max_nodes == node_id)
            return;
        if (arc_con.domain[x][y][dir][i])
        {

            // fill this node with i-th word
            int tx = x, ty = y;
            bool can_be_filled = 1;
            for (int pos = 0; pos < CSPify::len[x][y][dir]; pos++)
            {
                if (CrosswordGenerator::grid[tx][ty] != '.' && CrosswordGenerator::grid[tx][ty] != CrosswordGenerator::bag[length][arc_con.rebag[length][i]][pos])
                {
                    can_be_filled = 0;
                    break;
                }
                CrosswordGenerator::grid[tx][ty] = CrosswordGenerator::bag[length][arc_con.rebag[length][i]][pos];
                if (dir == 0)
                    ty++;
                else
                    tx++;
            }
            if (!can_be_filled)
            {
                for (auto pos : empty_spots)
                {
                    CrosswordGenerator::grid[x + dir * pos][y + (1 - dir) * pos] = '.';
                }
                continue;
            }

            // remove this word from all other nodes
            if (!repetition_allowed)
            {
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
            }

            // remove all words from domain of node
            for (int j = 0; j < arc_con.bag_size; j++)
            {
                if (i != j && arc_con.domain[x][y][dir][j])
                {
                    arc_con.domain[x][y][dir][j] = 0;
                    removed_domain.push_back(j);
                }
            }
            arc_con.domain[x][y][dir][i] = 2;

            grid_state.push_back(CrosswordGenerator::grid);
            adj.push_back(vector<int>());
            node_id++;

            adj[my_id].push_back(node_id);
            backtrack(node + 1, depth + 1);

            // revert back to original state
            for (auto pos : empty_spots)
            {
                CrosswordGenerator::grid[x + dir * pos][y + (1 - dir) * pos] = '.';
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
            arc_con.domain[x][y][dir][i] = 1;
            // arc_con = temp_obj;
        }
    }
}
void CrosswordBacktrackingTree::random_order_nodes()
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    for (int i = 0; i < CSPify::nodes.size(); i++)
        reordered_nodes.push_back(i);
    shuffle(reordered_nodes.begin(), reordered_nodes.end(), default_random_engine(seed));
}
void CrosswordBacktrackingTree::random_order_states()
{
    order.resize(adj.size());
    for (int i = 0; i < adj.size(); i++)
        order[i] = i;

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(order.begin(), order.end(), default_random_engine(seed));
    vector<vector<vector<char>>> new_grid_state(adj.size());
    for (int i = 0; i < adj.size(); i++)
        new_grid_state[i] = grid_state[order[i]];
    grid_state = new_grid_state;
}
void CrosswordBacktrackingTree::preprocess()
{
    node_id = 0;
    repetition_allowed = 0;
    arc_con.bag_size = bag_size;
    arc_con.init();
    arc_con.choose();
    arc_con.add_all_nodes();
    arc_con.ac3();
    adj.push_back(vector<int>());
    grid_state.push_back(CrosswordGenerator::grid);
}
void CrosswordBacktrackingTree::add_response(int x)
{
    student_response.push_back(x);
}
void CrosswordBacktrackingTree::compute_filled_nodes(vector<vector<int>> &nodes_filled)
{
    for (int n = 0; n < adj.size(); n++)
    {
        for (int node = 0; node < CSPify::nodes.size(); node++)
        {
            int x = CSPify::nodes[node].first.first, y = CSPify::nodes[node].first.second, dir = CSPify::nodes[node].second;
            int tx = x, ty = y;
            bool ok = 1;
            while (tx - x + 1 <= CSPify::len[x][y][dir] && ty - y + 1 <= CSPify::len[x][y][dir])
            {
                if (grid_state[n][tx][ty] == '.')
                {
                    ok = 0;
                    break;
                }
                if (dir)
                    tx++;
                else
                    ty++;
            }
            if (ok)
                nodes_filled[n].push_back(node);
        }
    }
}
bool CrosswordBacktrackingTree::is_valid_child(int parent, int child, vector<vector<int>> &nodes_filled)
{
    if (nodes_filled[parent].size() != nodes_filled[child].size() - 1)
        return 0;
    for (auto &node : nodes_filled[parent])
    {
        int x = CSPify::nodes[node].first.first, y = CSPify::nodes[node].first.second, dir = CSPify::nodes[node].second;
        int tx = x, ty = y;
        while (tx - x + 1 <= CSPify::len[x][y][dir] && ty - y + 1 <= CSPify::len[x][y][dir])
        {
            if (grid_state[parent][tx][ty] != grid_state[child][tx][ty])
            {
                return 0;
            }
            if (dir)
                tx++;
            else
                ty++;
        }
    }
    return 1;
}
void CrosswordBacktrackingTree::check()
{
    adj.resize(grid_state.size());
    result.assign(adj.size(), -1);
    map<int, vector<int>> indices;
    for (int i = 0; i < adj.size(); i++)
        indices[student_response[i]].push_back(i);

    auto cur = indices[0];
    vector<vector<int>> nodes_filled(adj.size());
    compute_filled_nodes(nodes_filled);
    queue<pair<int, int>> q;
    bool got_one = 0;
    for (auto &it : cur)
    {
        if (nodes_filled[it].size() == 0)
        {
            result[it] = 1;
            got_one = 1;
            q.push({0, it});
            for (auto &jt : cur)
            {
                if (result[jt] != 1)
                    result[jt] = -2;
            }
            break;
        }
    }
    if (!got_one)
    {
        for (auto &it : cur)
            result[it] = 0;
    }

    while (!q.empty())
    {
        auto f = q.front();
        q.pop();
        for (auto child : adj[f.first])
        {
            cur = indices[child];
            got_one = 0;
            for (auto &it : cur)
            {
                if (is_valid_child(f.second, it, nodes_filled))
                {
                    result[it] = 1;
                    got_one = 1;
                    q.push({child, it});
                    for (auto &jt : cur)
                    {
                        if (result[jt] != 1)
                            result[jt] = -2;
                    }
                    break;
                }
            }
            if (!got_one)
            {
                for (auto &it : cur)
                    result[it] = 0;
            }
        }
    }
}
void CrosswordBacktrackingTree::do_all_tasks()
{
    preprocess();
    random_order_nodes();
    backtrack(0, 0);
    random_order_states();
}
void CrosswordBacktrackingTree::startGame()
{
    cout << "Enter bag size : ";
    cin >> bag_size;
    cout << "Allow repetition of words : ";
    cin >> repetition_allowed;
    cout << "Maximum depth : ";
    cin >> max_depth;
    cout << "Maximum no of nodes: ";
    cin >> max_nodes;

    do_all_tasks();

    cout << "Adjacency list of recursion tree :\n";
    for (int i = 0; i < adj.size(); i++)
    {
        cout << i << " --> ";
        for (auto it : adj[i])
            cout << it << " ";
        cout << "\n";
    }

    for (int n = 0; n < adj.size(); n++)
    {
        for (int i = 1; i <= CrosswordGenerator::grid_size; i++)
        {
            for (int j = 1; j <= CrosswordGenerator::grid_size; j++)
            {
                cout << grid_state[n][i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    cout << "Enter your responses: \n";
    for (int i = 0; i < adj.size(); i++)
    {
        int x;
        cin >> x;
        add_response(x);
    }

    check();
    for (auto it : result)
        cout << it << " ";
    cout << "\n";
    // cout << "Solutions found at : ";
    // for (auto it : solution_indices)
    //     cout << it << " ";
    // cout << "\n";
    // while (1)
    // {
    //     int n;
    //     cout << "Enter node to see state : ";
    //     cin >> n;
    //     if (n >= adj.size())
    //         break;
    //     cout << "\nCrossword state :\n";
    //     for (int i = 1; i <= CrosswordGenerator::grid_size; i++)
    //     {
    //         for (int j = 1; j <= CrosswordGenerator::grid_size; j++)
    //         {
    //             cout << grid_state[n][i][j] << " ";
    //         }
    //         cout << "\n";
    //     }
    //     // cout << "\nDomain state :\n";
    //     // arc_con.domain = domain_state[n];
    //     // arc_con.print_bag();
    //     cout << "\n";
    // }
}
