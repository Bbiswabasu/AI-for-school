#include <bits/stdc++.h>
#include "crossword_generator.h"

int CrosswordGenerator::grid_size;
int uplen;

const int M=35;
vector<vector<char>> CrosswordGenerator::grid;
vector<pair<int,int>> CrosswordGenerator::moves;
vector<long long int> dist;
vector<long long int> fac;

void CrosswordGenerator::init()
{
	moves=vector<pair<int,int>>({{0,1},{1,0},{0,-1},{-1,0}});
	grid.resize(M,vector<char>(M));
	dist.resize(M);
	fac.resize(M);
	uplen=sqrt(grid_size)+3;
	srand(time(NULL));

	for(int i=0;i<2*grid_size;i++)
	{
		for(int j=0;j<2*grid_size;j++)
		{
			grid[i][j]='#';
		}
	}

	for(int i=1;i<grid_size+1;i++)
	{
		for(int j=1;j<grid_size+1;j++)
		{
			grid[i][j]='.';
			if((i&1)==0 and (j&1)==0)
			{
				grid[i][j]='#';
			}
		}
	}
}

void CrosswordGenerator::form_grid()
{
	int md=1<<(uplen);
	for(int i=1;i<=grid_size;i++)
	{
		if((i&1))
		{
			int val;
			int len;
			int pos=1;
			while(pos<=grid_size)
			{
				while(1)
				{
				 	val=rand()%(md)+1;
					for(int j=0;j<=uplen+1;j++)
					{
						if(val<=dist[j])
						{
							len=j;
							break;
						}
					}			
					if(len>2 and len<=uplen)
					{
						break;
					}
				}
				int pl;
				if(pos==1)
					pl=rand()%(uplen-3);
				else
				{
					pl=rand()%(uplen-4);
				}
				for(int j=pos;j<pos+pl;j++)
				{
					grid[i][j]='#';
				}
				for(int j=pl+pos;j<pl+pos+len;j++)
				{
					grid[i][j]='.';
				}		
				grid[i][pl+pos+len]='#';	
				pos+=pl+len+1;
				grid[i][grid_size+1]='#';			
			}

		}
	}

}

void CrosswordGenerator::print_grid()
{
	for(int i=1;i<grid_size+1;i++)
	{
		for(int j=1;j<grid_size+1;j++)
		{
			cout<<grid[i][j]<<" ";
		}
		cout<<"\n";
	}	
	cout<<"\n";
}

void CrosswordGenerator::transpose()
{
	for(int i=1;i<=grid_size;i++)
	{
		for(int j=1;j<i;j++)
		{
			swap(grid[i][j],grid[j][i]);
		}
	}
	
}

void CrosswordGenerator::remove2()
{
	for(int i=1;i<=grid_size+1;i++)
	{
		if((i&1)==0)
		{
			continue;
		}
		int ct=0;
		for(int j=1;j<=grid_size+1;j++)
		{
			if(grid[i][j]=='.')
				ct+=1;
			else
			{
				if(ct==2)
				{
					if((j&1))
					{
						grid[i][j-1]='#';
					}
					else
					{
						grid[i][j-2]='#';
					}
				}
				ct=0;
			}
		}
	}
}
void CrosswordGenerator::remove1()
{
	for(int i=1;i<grid_size+1;i++)
	{
		for(int j=1;j<grid_size+1;j++)
		{
			int cur=0;
			for(int k=0;k<4;k++)
			{
				if(grid[i+moves[k].first][j+moves[k].second]=='#')
					cur++;
			}
			if(cur==4)
			{
				grid[i][j]='#';
			}			
		}
	}	
}

void CrosswordGenerator::distribution() //Makes binomial distribution
{
	fac[0]=1;
	for(int i=1;i<=uplen;i++)
	{
		fac[i]=i*fac[i-1];
	}
	dist[0]=1;
	for(int i=1;i<=uplen;i++)
	{
		dist[i]=fac[uplen]/(fac[i]*fac[uplen-i])+dist[i-1];
	}
}

void CrosswordGenerator::adjust()
{
	remove2();
	transpose();
	remove2();
	transpose();
	remove1();

	if(rand()%2)
	{
		transpose();
	}
}