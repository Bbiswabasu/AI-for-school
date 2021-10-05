#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <crossword_generator.h>
#include "CSPify.h"
#include "node_consistency.h"

using namespace std;

NodeConsistency::NodeConsistency() {}
vector<pair<int, int>> NodeConsistency::get_shuffled_bag_ind() const { return shuffled_bag_ind; }
vector<string> NodeConsistency::get_shuffled_bag() const { return shuffled_bag; }
vector<int> NodeConsistency::get_result() const { return result; }
vector<vector<int>> NodeConsistency::get_tick_cross() const { return tick_cross; }

void NodeConsistency::init()
{
    rebag.clear();
    rebag.resize(CrosswordGenerator::grid_size + 5, vector<int>());
    shuffled_bag_ind.clear();
    shuffled_bag.clear();
    student_answers.resize(CSPify::nodes.size());
}
void NodeConsistency::restore_bag(int len, int ind)
{
    shuffled_bag_ind.push_back({len, ind});
    rebag[len].push_back(ind);
    // shuffled_bag.push_back(CrosswordGenerator::bag[len][ind]);
}
void NodeConsistency::choose()
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    binomial_distribution<int> distribution(4, 0.75);
    for (int i = 3; i <= CrosswordGenerator::grid_size; i++)
    {
        vector<int> tp;
        for (int j = 0; j < CrosswordGenerator::bag[i].size(); j++)
        {
            tp.push_back(j);
        }
        shuffle(tp.begin(), tp.end(), default_random_engine(seed));
        int szbag = 1 + distribution(generator);
        for (int j = 0; j < szbag; j++)
        {
            rebag[i].push_back(tp[j]);
            shuffled_bag_ind.push_back({i, tp[j]});
        }
    }
    shuffle(shuffled_bag_ind.begin(), shuffled_bag_ind.end(), default_random_engine(seed));
    for (auto it : shuffled_bag_ind)
        shuffled_bag.push_back(CrosswordGenerator::bag[it.first][it.second]);
}

void NodeConsistency::print_bag()
{
    cout << "Length-wise : \n";
    for (int i = 3; i <= CrosswordGenerator::grid_size; i++)
    {
        for (auto it : rebag[i])
            cout << CrosswordGenerator::bag[i][it] << " ";
        cout << "\n";
    }
    cout << "\nAll shuffled :\n";
    for (auto it : shuffled_bag)
        cout << it << " ";
    cout << "\n";
}

void NodeConsistency::add_response(int node, int resp)
{
    student_answers[node].push_back(resp);
}
void NodeConsistency::check()
{
    result.clear();
    tick_cross.clear();
    result.resize(CSPify::nodes.size());
    tick_cross.resize(CSPify::nodes.size(), vector<int>(shuffled_bag_ind.size()));
    for (int i = 0; i < CSPify::nodes.size(); i++)
    {
        bool ok = 1;
        auto node = CSPify::nodes[i];
        int len = CSPify::len[node.first.first][node.first.second][node.second];
        for (int j = 0; j < student_answers[i].size(); j++)
        {
            if ((student_answers[i][j] && len != shuffled_bag_ind[j].first) || (!student_answers[i][j] && len == shuffled_bag_ind[j].first))
            {
                ok = 0;
                tick_cross[i][j] = 0;
            }
            else
                tick_cross[i][j] = 1;
        }
        result[i] = ok;
    }
}
void NodeConsistency::startGame()
{
    init();
    choose();
    print_bag();
    int i = 0;
    for (auto it : CSPify::nodes)
    {
        cout << it.first.first << "-" << it.first.second << "-" << (it.second ? "D" : "A") << "\n";
        for (int j = 0; j < shuffled_bag.size(); j++)
        {
            int d;
            cin >> d;
            add_response(i, d);
        }
        i++;
    }
    check();
    for (int i = 0; i < CSPify::nodes.size(); i++)
    {
        for (int j = 0; j < shuffled_bag.size(); j++)
            cout << tick_cross[i][j] << " ";
        cout << "-> " << result[i] << "\n";
    }
}
