#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <crossword_generator.h>
#include "CSPify.h"
#include "node_consistency.h"

using namespace std;

void NodeConsistency::init()
{
    rebag.clear();
    rebag.resize(CrosswordGenerator::grid_size + 5, vector<int>());
    shuffled_bag.clear();
    student_answers.resize(CSPify::nodes.size());
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
            shuffled_bag.push_back({i, tp[j]});
        }
    }
    shuffle(shuffled_bag.begin(), shuffled_bag.end(), default_random_engine(seed));
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
        cout << CrosswordGenerator::bag[it.first][it.second] << " ";
    cout << "\n";
}

void NodeConsistency::add_response(int id, int word_index)
{
    student_answers[id].push_back(word_index);
}
void NodeConsistency::check()
{
    result.clear();
    for (int i = 0; i < CSPify::nodes.size(); i++)
    {
        bool ok = 1;
        auto node = CSPify::nodes[i];
        int len = CSPify::len[node.first.first][node.first.second][node.second];
        if (student_answers[i].size() != rebag[len].size())
            ok = 0;
        else
        {
            for (auto it : student_answers[i])
            {
                if (len != shuffled_bag[it].first)
                {
                    ok = 0;
                    break;
                }
            }
        }
        result.push_back(ok);
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
        cout << it.first.first << "-" << it.first.second << "-" << (it.second ? "D" : "A") << " ";
        while (1)
        {
            int n;
            cin >> n;
            if (n == -1)
                break;
            add_response(i, n);
        }
        i++;
    }
    check();
    for (int i = 0; i < CSPify::nodes.size(); i++)
        cout << result[i] << "\n";
}
