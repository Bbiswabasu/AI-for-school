#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include "arc_consistency.h"
#include "crossword_generator.h"
#include "CSPify.h"
using namespace std;

const int M = 35;

void ArcConsistency::init()
{
	rebag.assign(CrosswordGenerator::grid_size + 2, vector<int>(szbag));
	domain.assign(M, vector<vector<vector<int>>>(M, vector<vector<int>>(2, vector<int>(szbag, 1))));
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
		for (int j = 0; j < szbag; j++)
		{
			rebag[i][j] = tp[j];
			cout << (CrosswordGenerator::bag[i][tp[j]]);
			cout << " ";
			;
		}
		cout << "\n";
	}
	cout << "\n";
}

void ArcConsistency::print_bag()
{
	int i, j, k;
	for (auto node : CSPify::nodes)
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

		for (int cur = 0; cur < szbag; cur++)
		{
			if (domain[i][j][k][cur])
				cout << CrosswordGenerator::bag[length][rebag[length][cur]] << " ";
		}
		cout << "\n";
	}
}

bool ArcConsistency::revise(pair<pair<int, int>, int> fp, pair<pair<int, int>, int> sp)
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

	int gf = 0;
	for (int i = 0; i < szbag; i++)
	{
		int fpos = rebag[flength][i];
		string fcur = CrosswordGenerator::bag[flength][fpos];
		int top = 0;
		if (domain[fx][fy][fbin][i] != 1)
			continue;

		int flag = 0;
		if (fbin == 0)
		{
			for (int j = 0; j < szbag; j++)
			{
				if (!domain[sx][sy][sbin][j])
					continue;
				int spos = rebag[slength][j];
				string scur = CrosswordGenerator::bag[slength][spos];
				if (fcur[inty - fy] == scur[intx - sx])
				{
					flag = 1;
					break;
				}
			}
		}
		else
		{
			for (int j = 0; j < szbag; j++)
			{
				if (!domain[sx][sy][sbin][j])
					continue;
				int spos = rebag[slength][j];
				string scur = CrosswordGenerator::bag[slength][spos];
				if (fcur[intx - fx] == scur[inty - sy])
				{
					flag = 1;
					break;
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

void ArcConsistency::ac3()
{
	deque<pair<pair<pair<int, int>, int>, pair<pair<int, int>, int>>> temp_q = CSPify::q;

	while (!temp_q.empty())
	{
		auto tp = temp_q.front();
		temp_q.pop_front();
		auto fp = tp.first;
		auto sp = tp.second;
		if (revise(fp, sp))
		{
			int x = fp.first.first;
			int y = fp.first.second;
			int bin = fp.second;
			for (int i = 0; i < CSPify::graph[x][y][bin].size(); i++)
			{
				auto val = CSPify::graph[x][y][bin][i];
				if (val == sp.first)
				{
					continue;
				}
				temp_q.push_back({{val, 1 - bin}, fp});
			}
		}
	}
}

void ArcConsistency::startGame()
{
	cout << "Enter bag size : ";
	cin >> szbag;
	init();
	choose();
	ac3();
	print_bag();
}