#include <bits/stdc++.h>
#include "arc_consistency.h"
#include "crossword_generator.h"
#include "CSPify.h"
using namespace std;

const int M=35;

int szbag;
vector<int> notdom[M][M][2]; 
vector<int> bagct;
vector<vector<int>> rebag;

void ArcConsistency::choose()
{
	for(int i=3;i<CrosswordGenerator::grid_size+1;i++)
	{
		int tp[bagct[i]];
		for(int j=0;j<bagct[i]-1;j++)
		{
			tp[j]=j;
		}
		random_shuffle(tp,tp+bagct[i]);
		for(int j=0;j<szbag;j++)
		{
			rebag[i][j]=tp[j];
			cout<<(CrosswordGenerator::bag[i][tp[j]]);
			cout<<" ";;
		}
		cout<<"\n";
	}
	cout<<"\n";
}

void ArcConsistency::print_bag()
{
	int i,j,k;
	for(auto node:CSPify::nodes)
	{
		i=node.first.first;
		j=node.first.second;
		k=node.second;

		cout<<i;cout<<"-";
		cout<<j;cout<<"-";
		cout<<(k?"D":"A");cout<<"\n";
		int length=CSPify::CSPify::len[i][j][k];

		vector<int> temp;
		int flag;
		for(int cur=0;cur<szbag;cur++)
		{
			flag=0;
			for(auto x: notdom[i][j][k])
			{
				if(cur==x)
				{
					flag=1;
				}
			}	
			if(!flag)
			{
				temp.push_back(cur);
			}					
		}
		for(auto x: temp)
		{
			int pos=rebag[length][x];
			string s=CrosswordGenerator::bag[length][pos];
			cout<<s;cout<<" ";;
		}
		cout<<"\n";
	}
}

bool ArcConsistency::revise(pair<pair<int,int>,int> fp,pair<pair<int,int>,int> sp)
{
	int fx=fp.first.first;
	int fy=fp.first.second;
	int fbin=fp.second;

	int sx=sp.first.first;
	int sy=sp.first.second;
	int sbin=sp.second;

	int flength=CSPify::len[fx][fy][fbin];
	int slength=CSPify::len[sx][sy][sbin];

	int intx;
	int inty;

	if(fbin==0)
	{
		intx=fx;
		inty=sy;
	}
	else
	{
		intx=sx;
		inty=fy;
	}

	int gf=0;
	for(int i=0;i<szbag;i++)
	{
		int fpos=rebag[flength][i];
		string fcur=CrosswordGenerator::bag[flength][fpos];
		int top=0;
		for(auto x: notdom[fx][fy][fbin])
		{
			if(x==i)
			{
				top=1;
			}
		}
		if(top)
		{
			continue;
		}

		int flag=0;
		if(fbin==0)
		{
			for(int j=0;j<szbag;j++)
			{
				int top=0;
				for(auto x: notdom[sx][sy][sbin])
				{
					if(x==j)
					{
						top=1;
					}
				}
				if(top)
				{
					continue;
				}
				int spos=rebag[slength][j];
				string scur=CrosswordGenerator::bag[slength][spos];
				if(fcur[inty-fy]==scur[intx-sx])
				{
					flag=1;
				}
			}			
		}
		else
		{
			for(int j=0;j<szbag;j++)
			{
				int top=0;
				for(auto x: notdom[sx][sy][sbin])
				{
					if(x==j)
					{
						top=1;
					}
				}
				if(top)
				{
					continue;
				}
				int spos=rebag[slength][j];
				string scur=CrosswordGenerator::bag[slength][spos];
				if(fcur[intx-fx]==scur[inty-sy])
				{
					flag=1;
				}
			}						
		}
		if(!flag)
		{
			gf=1;
			notdom[fx][fy][fbin].push_back(i);

		}
	}
	return gf;
}

void ArcConsistency::ac3()
{
    deque <pair<pair<pair<int,int>,int>,pair<pair<int,int>,int>>> temp_q=CSPify::q;

	while(!temp_q.empty())
	{
		auto tp=temp_q.front();
		temp_q.pop_front();
		auto fp=tp.first;
		auto sp=tp.second;
		if(revise(fp,sp))
		{
			int x=fp.first.first;
			int y=fp.first.second;
			int bin=fp.second;
			for(int i=0;i<CSPify::graph[x][y][bin].size();i++)
			{
				auto val=CSPify::graph[x][y][bin][i];
				if(val==sp.first)
				{
					continue;
				}
				temp_q.push_back({{val,1-bin},fp});
			}
		}
	}
}


void ArcConsistency::startGame()
{
    cout<<"Enter bag size : ";
    cin>>szbag;
    bagct=vector<int>({0,0,0,120,240,190,160,130,80,40,30,10});
    rebag.resize(12,vector<int>(50));
    choose();
    ac3();
    print_bag();
}