#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <set>
#include "arc_consistency.h"
#include "crossword_generator.h"
#include "CSPify.h"
using namespace std;

const int M = 35;

ArcConsistency::ArcConsistency() {}
int ArcConsistency::get_bag_size() const { return bag_size; }
void ArcConsistency::set_bag_size(int x) { bag_size = x; }
int ArcConsistency::get_num_nodes() const { return num_nodes; }
void ArcConsistency::set_num_nodes(int x) { num_nodes = x; }
vector<pair<pair<int, int>, int>> ArcConsistency::get_nodes() const { return nodes; }
vector<vector<int>> ArcConsistency::get_rebag() const { return rebag; }
vector<vector<string>> ArcConsistency::get_word_bag() const { return word_bag; }
vector<int> ArcConsistency::get_result() const { return result; }
vector<vector<int>> ArcConsistency::get_tick_cross() const { return tick_cross; }
vector<vector<vector<pair<int, int>>>> ArcConsistency::get_consistency_graph() const { return consistency_graph; }

void ArcConsistency::init()
{
	rebag.assign(CrosswordGenerator::grid_size + 2, vector<int>(bag_size));
	domain.assign(M, vector<vector<vector<int>>>(M, vector<vector<int>>(2, vector<int>(bag_size, 1))));
	student_domain.assign(M, vector<int>(bag_size, 1));
	nodes.clear();
	srand((unsigned)time(NULL));
}

void ArcConsistency::restore_bag(int i, int j, int val)
{
	rebag[i][j] = val;
}
void ArcConsistency::restore_nodes(int x, int y, int dir)
{
	nodes.push_back({{x, y}, dir});
}

void ArcConsistency::choose()
{
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	for (int i = 3; i <= CrosswordGenerator::grid_size; i++)
	{
		vector<int> tp;
		for (int j = 0; j < CrosswordGenerator::bag[i].size(); j++)
		{
			tp.push_back(j);
		}
		shuffle(tp.begin(), tp.end(), default_random_engine(seed));
		for (int j = 0; j < bag_size; j++)
		{
			rebag[i][j] = tp[j];
		}
	}
	word_bag.resize(nodes.size());
	for (int i = 0; i < nodes.size(); i++)
	{
		int len = CSPify::len[nodes[i].first.first][nodes[i].first.second][nodes[i].second];
		for (auto jt : rebag[len])
		{
			word_bag[i].push_back(CrosswordGenerator::bag[len][jt]);
		}
	}
}

void ArcConsistency::print_bag()
{
	int i, j, k;
	for (auto node : nodes)
	{
		i = node.first.first;
		j = node.first.second;
		k = node.second;

		cout << i;
		cout << "-";
		cout << j;
		cout << "-";
		cout << (k ? "D" : "A");
		cout << "\n";
		int length = CSPify::len[i][j][k];

		for (int cur = 0; cur < bag_size; cur++)
		{
			if (domain[i][j][k][cur])
				cout << CrosswordGenerator::bag[length][rebag[length][cur]] << " ";
		}
		cout << "\n";
	}
}

bool ArcConsistency::revise(pair<pair<int, int>, int> fp, pair<pair<int, int>, int> sp, bool graph_mode)
{
	int fx = fp.first.first;
	int fy = fp.first.second;
	int fbin = fp.second;

	int sx = sp.first.first;
	int sy = sp.first.second;
	int sbin = sp.second;

	int flength = CSPify::len[fx][fy][fbin];
	int slength = CSPify::len[sx][sy][sbin];

	int intx;
	int inty;

	if (fbin == 0)
	{
		intx = fx;
		inty = sy;
	}
	else
	{
		intx = sx;
		inty = fy;
	}

	int ind1 = -1, ind2 = -1;
	if (graph_mode)
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i] == fp)
				ind1 = i;
			if (nodes[i] == sp)
				ind2 = i;
		}
		if (ind1 > ind2)
			return 0;
	}

	int gf = 0;
	for (int i = 0; i < bag_size; i++)
	{
		int fpos = rebag[flength][i];
		string fcur = CrosswordGenerator::bag[flength][fpos];
		int top = 0;
		if (domain[fx][fy][fbin][i] != 1)
			continue;

		int flag = 0;
		if (fbin == 0)
		{
			for (int j = 0; j < bag_size; j++)
			{
				if (!domain[sx][sy][sbin][j])
					continue;
				int spos = rebag[slength][j];
				string scur = CrosswordGenerator::bag[slength][spos];
				if (fcur[inty - fy] == scur[intx - sx])
				{
					flag = 1;
					if (!graph_mode)
						break;
					consistency_graph[ind1][i].push_back({ind2, j});
				}
			}
		}
		else
		{
			for (int j = 0; j < bag_size; j++)
			{
				if (!domain[sx][sy][sbin][j])
					continue;
				int spos = rebag[slength][j];
				string scur = CrosswordGenerator::bag[slength][spos];
				if (fcur[intx - fx] == scur[inty - sy])
				{
					flag = 1;
					if (!graph_mode)
						break;
					consistency_graph[ind1][i].push_back({ind2, j});
				}
			}
		}
		if (!flag)
		{
			gf = 1;
			domain[fx][fy][fbin][i] = 0;
		}
	}
	return gf;
}

void ArcConsistency::add_node(pair<pair<int, int>, int> n)
{
	nodes.push_back(n);
}

void ArcConsistency::add_all_nodes()
{
	for (auto node : CSPify::nodes)
		nodes.push_back(node);
}

void ArcConsistency::build_queue()
{
	while (!q.empty())
		q.pop();
	nodes_set.clear();
	//insert all edges
	for (auto node : nodes)
		nodes_set.insert(node);
	for (auto node : nodes)
	{
		for (auto it : CSPify::graph[node.first.first][node.first.second][node.second])
		{
			if (nodes_set.find({it, 1 - node.second}) != nodes_set.end())
				q.push({node, {it, 1 - node.second}});
		}
	}
}

void ArcConsistency::ac3()
{
	build_queue();

	while (!q.empty())
	{
		auto tp = q.front();
		q.pop();
		auto fp = tp.first;
		auto sp = tp.second;
		if (revise(fp, sp, 0))
		{
			int x = fp.first.first;
			int y = fp.first.second;
			int bin = fp.second;
			for (int i = 0; i < CSPify::graph[x][y][bin].size(); i++)
			{
				auto val = CSPify::graph[x][y][bin][i];
				if (nodes_set.find({val, 1 - bin}) == nodes_set.end())
					continue;

				if (val == sp.first)
				{
					continue;
				}
				q.push({{val, 1 - bin}, fp});
			}
		}
	}
}

void ArcConsistency::build_consistency_graph()
{
	build_queue();
	consistency_graph.resize(nodes.size(), vector<vector<pair<int, int>>>(bag_size, vector<pair<int, int>>()));
	while (!q.empty())
	{
		auto tp = q.front();
		q.pop();
		auto fp = tp.first;
		auto sp = tp.second;
		revise(fp, sp, 1);
	}
}
void ArcConsistency::print_consistency_graph()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < bag_size; j++)
		{
			cout << nodes[i].first.first << "-" << nodes[i].first.second << "-" << nodes[i].second << " ";
			for (auto it : consistency_graph[i][j])
			{
				cout << it.first << "-" << it.second << " ";
			}
			cout << "\n";
		}
	}
}
void ArcConsistency::choose_x_nodes(int x)
{
	vector<vector<vector<bool>>> vis(CrosswordGenerator::grid_size + 1, vector<vector<bool>>(CrosswordGenerator::grid_size + 1, vector<bool>(2, 0)));
	queue<pair<pair<int, int>, int>> bfs;
	auto start = CSPify::nodes[rand() % ((CSPify::nodes).size())];
	int cnt = 1;
	nodes.push_back(start);
	vis[start.first.first][start.first.second][start.second] = 1;
	bfs.push(start);
	if (x == 1)
		return;
	while (!bfs.empty())
	{
		auto f = bfs.front();
		bfs.pop();
		for (auto it : CSPify::graph[f.first.first][f.first.second][f.second])
		{
			if (vis[it.first][it.second][1 - f.second])
				continue;
			vis[it.first][it.second][1 - f.second] = 1;
			cnt++;
			nodes.push_back({it, {1 - f.second}});
			if (cnt == x)
				break;
			bfs.push({it, {1 - f.second}});
		}
		if (cnt == x)
			break;
	}
}
void ArcConsistency::add_response(int node, int ind, int resp)
{
	student_domain[node][ind] = resp;
}

void ArcConsistency::check()
{
	result.clear();
	tick_cross.clear();
	result.resize(nodes.size());
	tick_cross.resize(nodes.size(), vector<int>(bag_size));
	for (int i = 0; i < nodes.size(); i++)
	{
		bool ok = 1;
		for (int j = 0; j < bag_size; j++)
		{
			if (domain[nodes[i].first.first][nodes[i].first.second][nodes[i].second][j] != student_domain[i][j])
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

void ArcConsistency::startGame()
{
	cout << "Enter bag size : ";
	cin >> bag_size;
	cout << "Enter number of nodes for AC : ";
	cin >> num_nodes;
	init();
	choose_x_nodes(num_nodes);
	choose();
	ac3();

	cout << "Answer :\n";
	print_bag();
	cout << "\n"
		 << "Mark each word as whether they are AC :\n";
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i].first.first << "-" << nodes[i].first.second << "-" << (nodes[i].second ? "D" : "A") << "\n";
		int len = CSPify::len[nodes[i].first.first][nodes[i].first.second][nodes[i].second];
		for (auto it : rebag[len])
			cout << CrosswordGenerator::bag[len][it] << " ";
		cout << "\n";
		for (int j = 0; j < bag_size; j++)
		{
			int d;
			cin >> d;
			add_response(i, j, d);
		}
	}
	check();
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < bag_size; j++)
			cout << tick_cross[i][j] << " ";
		cout << "-> " << result[i] << "\n";
	}
	build_consistency_graph();
	print_consistency_graph();
}