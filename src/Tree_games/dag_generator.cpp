#include <iostream>
#include <ctime>
#include <queue>
#include <random>
#include <chrono>
#include "dag_generator.h"
using namespace std;

int DAGGenerator::num_vars; //number of variables
int DAGGenerator::num_nodes;

vector<vector<int>> DAGGenerator::adj;			  //stores adjacency list
vector<string> DAGGenerator::content;			  //stores content of each node
vector<int> DAGGenerator::values;				  //stores values at each node
vector<string> DAGGenerator::operators;			  //stores list of operators
vector<int> DAGGenerator::indeg;				  //stores indegree of each node
vector<string> DAGGenerator::expressions;		  //stores expression at each node
vector<int> DAGGenerator::x_coor;				  //stores x coordinate of each node
vector<int> DAGGenerator::y_coor;				  //stores y coordinate of each node
vector<vector<int>> DAGGenerator::edge_carvature; //stores carvature of each edge

DAGGenerator::DAGGenerator() {}

int DAGGenerator::get_num_vars() const { return num_vars; }
void DAGGenerator::set_num_vars(int x_) { num_vars = x_; }
int DAGGenerator::get_num_nodes() const { return num_nodes; }
void DAGGenerator::set_num_nodes(int x_) { num_nodes = x_; }
vector<vector<int>> DAGGenerator::get_adj() const { return adj; }
vector<string> DAGGenerator::get_content() const { return content; }
vector<int> DAGGenerator::get_values() const { return values; }
vector<string> DAGGenerator::get_operators() const { return operators; }
vector<int> DAGGenerator::get_indeg() const { return indeg; }
vector<string> DAGGenerator::get_expressions() const { return expressions; }
vector<int> DAGGenerator::get_x_coor() const { return x_coor; }
vector<int> DAGGenerator::get_y_coor() const { return y_coor; }
vector<vector<int>> DAGGenerator::get_edge_carvature() const { return edge_carvature; }

void DAGGenerator::restore_dag(char name, int node, int val, string sval)
{
	if (name == 'a')
		adj[node].push_back(val);
	else if (name == 'c')
		content[node] = sval;
	else if (name == 'v')
		values[node] = val;
	else if (name == 'x')
		x_coor[node] = val;
	else if (name == 'y')
		y_coor[node] = val;
	else if (name == 'e')
		edge_carvature[node].push_back(val);
}
void DAGGenerator::init()
{
	id = 0;
	var_name = 'a';
	operators = vector<string>({"&", "|", "=>", "<=>"});
	adj.clear();
	content.clear();
	values.clear();
	indeg.clear();
	expressions.clear();
	srand((unsigned)time(NULL));
	adj.resize(num_nodes, vector<int>());
	content.resize(adj.size());
	expressions.resize(adj.size());
	values.resize(adj.size());
	x_coor.resize(num_nodes);
	y_coor.resize(num_nodes);
	edge_carvature.resize(num_nodes, vector<int>());
}
int DAGGenerator::random(int a, int b, int x)
{
	return a + x % (b - a + 1);
}
void DAGGenerator::generate_dag()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> uniform(0, 100);
	num_not = random(0, (num_vars + 1) / 2, uniform(generator)); //numbers of NOT nodes to be inserted
	num_nodes += num_not;
	adj.resize(num_nodes, vector<int>());
	indeg.resize(num_nodes, 0);
	num_nodes -= num_not;

	//Randomly connect nodes following topological order
	for (int i = 0; i < num_nodes - num_vars; i++)
	{
		int succ1;
		if (indeg[i + 1] == 0) // to ensure non-sink nodes have indegree>=1
			succ1 = i + 1;
		else
			succ1 = random(i + 1, num_nodes - 1, uniform(generator));
		int succ2;
		if (succ1 != i + 1)
			succ2 = random(i + 1, succ1 - 1, uniform(generator));
		else
			succ2 = random(succ1 + 1, num_nodes - 1, uniform(generator));
		adj[i].push_back(succ1);
		adj[i].push_back(succ2);
		indeg[succ1]++;
		indeg[succ2]++;
	}

	//Ensure sink nodes have indegree>=1
	int i = 0, j = num_nodes - num_vars;
	while (j < num_nodes)
	{
		if (indeg[j] >= 1)
		{
			j++;
			continue;
		}
		if (indeg[adj[i][0]] > 1)
		{
			indeg[adj[i][0]]--;
			int succ2 = adj[i][1];
			adj[i].pop_back();
			adj[i].pop_back();
			adj[i].push_back(j);
			adj[i].push_back(succ2);
			indeg[j]++;
			j++;
		}
		else if (indeg[adj[i][1]] > 1)
		{
			indeg[adj[i][1]]--;
			adj[i].pop_back();
			adj[i].push_back(j);
			indeg[j]++;
			j++;
		}
		else
			i++;
	}

	//Add NOT nodes in between
	num_nodes += num_not;
	for (int i = num_nodes - 1; i >= num_nodes - num_not; i--)
	{
		int index = random(0, num_nodes - num_not - num_vars - 1, uniform(generator));
		adj[i].push_back(adj[index][1]);
		adj[index].pop_back();
		adj[index].push_back(i);
	}
}

void DAGGenerator::assign_content()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> uniform(0, 100);
	content.resize(adj.size());
	expressions.resize(adj.size());
	for (int i = 0; i < adj.size(); i++)
	{
		if (adj[i].size() == 0)
			content[i] = var_name++;
		else if (adj[i].size() == 1)
			content[i] = "~";
		else
			content[i] = operators[uniform(generator) % 4];
	}
}

void DAGGenerator::assign_values()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> uniform(0, 100);
	values.resize(adj.size());
	for (int i = 0; i < adj.size(); i++)
	{
		if (!isalpha(content[i][0]))
			continue;
		values[i] = uniform(generator) % 2;
	}
}

void DAGGenerator::display_dag()
{
	cout << "Adjacency list and content of each node :\n";
	for (int i = 0; i < adj.size(); i++)
	{
		cout << i << " " << content[i] << " ";
		for (auto it : adj[i])
		{
			cout << it << " ";
		}
		cout << "\n";
	}
}
void DAGGenerator::compute_graph_layout()
{
	//compute y coordinates
	y_coor.resize(adj.size());
	queue<int> q;
	q.push(0);
	y_coor[0] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (auto it : adj[u])
		{
			y_coor[it] = y_coor[u] + 1;
			q.push(it);
		}
	}

	//compute x coordinates
	x_coor.resize(adj.size());
	vector<int> count(num_nodes, 0);
	for (int i = 0; i < num_nodes; i++)
	{
		x_coor[i] = count[y_coor[i]];
		count[y_coor[i]]++;
	}

	//compute carvature for each edge
	edge_carvature.clear();
	edge_carvature.resize(adj.size(), vector<int>(2, 0));
	for (int i = 0; i < num_nodes; i++)
	{
		int j = 0;
		for (auto it : adj[i])
		{
			//for each edge check if there is other node who is collinear
			for (int k = 0; k < num_nodes; k++)
			{
				if (k == i || k == it)
					continue;
				int i_x = x_coor[i], i_y = y_coor[i];
				int it_x = x_coor[it], it_y = y_coor[it];
				int k_x = x_coor[k], k_y = y_coor[k];
				if ((i_x - it_x) * (it_y - k_y) == (it_x - k_x) * (i_y - it_y) && (k_y > i_y && k_y < it_y))
				{
					edge_carvature[i][j] = 2 * (j - 0.5) * (y_coor[it] - y_coor[i]);
					break;
				}
			}
			j++;
		}
	}
}
void DAGGenerator::do_all_tasks()
{
	init();
	generate_dag();
	assign_content();
	display_dag();
	assign_values();
	compute_graph_layout();
}
