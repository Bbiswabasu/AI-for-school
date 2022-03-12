// Demonstrate how to take students through the concepts modelled as Hyper-graph
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <fstream>
#include "concept_graph.h"
using namespace std;

ConceptGraph::ConceptGraph() {}
vector<int> ConceptGraph::get_status() const { return status; }
vector<int> ConceptGraph::get_completed() const { return completed; }

void ConceptGraph::init()
{
	graph = vector<vector<vector<int>>>({{},
										 {{0}},
										 {},
										 {},
										 {},
										 {{4}},
										 {{5}},
										 {{6}},
										 {{7}}});
	int v = graph.size();
	completed.assign(v, 0); // set all as not completed
	status.assign(v, -1);
}

// finds whether a certain concept can be attempted by student depending on status of pre-requisites
void ConceptGraph::compute_individual_status(int c)
{
	if (status[c] != -1)
		return;

	for (auto &it : graph[c])
	{
		bool OR = 0;
		for (auto &jt : it)
		{
			if (completed[jt] == 1)
			{
				compute_individual_status(jt);
				if (status[jt] == 1)
				{
					OR = 1;
					break;
				}
			}
		}
		if (OR == 0)
		{
			status[c] = 0;
			return;
		}
	}
	status[c] = 1;
}
void ConceptGraph::compute_status()
{
	for (int i = 0; i < graph.size(); i++)
	{
		compute_individual_status(i);
	}
}

void ConceptGraph::mark_complete(int c)
{
	completed[c] = 1;
}

void ConceptGraph::showMenu()
{
	init();

	string s;
	while (1)
	{
		cin >> s;
		if (s == "exit")
			break;
		if (s == "comp")
		{
			int n;
			cin >> n;
			completed[n] = 1;
		}
		if (s == "incomp")
		{
			int n;
			cin >> n;
			completed[n] = 0;
		}
		if (s == "status")
		{
			compute_status();
			for (auto it : status)
				cout << it << " ";
		}
		cout << "\n";
	}
}
