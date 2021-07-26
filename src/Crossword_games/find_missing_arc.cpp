#include <iostream>
#include "find_missing_arc.h"
#include "CSPify.h"
using namespace std;

void FindMissingArc::startGame()
{
	cout<<"Find the missing constraint for the above crossword grid :\n";
	int numofarcs=CSPify::q.size();
	int temp=rand()%numofarcs;
	int i=-1;
	pair<pair<pair<int,int>,int>,pair<pair<int,int>,int> > ans;
	for(auto cur: CSPify::q)
	{
		i++;
		if(i%2 != temp%2)
		continue;
		if(i!=temp)
		{
			cout<<cur.first.first.first;cout<<"-";
			cout<<cur.first.first.second;cout<<"-";
			cout<<(cur.first.second?"D":"A");cout<<" ";;

			cout<<cur.second.first.first;cout<<"-";
			cout<<cur.second.first.second;cout<<"-";
			cout<<(cur.second.second?"D":"A");cout<<" ";;
			cout<<"\n";
		}
		else
		{
			ans=cur;
		}
	}


	cout<<"Ans:\n";

	// i=temp;
	cout<<ans.first.first.first;cout<<"-";
	cout<<ans.first.first.second;cout<<"-";
	cout<<(ans.first.second?"D":"A");cout<<" ";;

	cout<<ans.second.first.first;cout<<"-";
	cout<<ans.second.first.second;cout<<"-";
	cout<<(ans.second.second?"D":"A");cout<<" ";;
	cout<<"\n";

}
