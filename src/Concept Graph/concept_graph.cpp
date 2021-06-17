//Demonstrate how to take students through the concepts modelled as Hyper-graph
#include <bits/stdc++.h>
using namespace std;

int v,e;
vector<string> concepts_name;
vector<vector<int>> inc_mat;
vector<int> concept_state;

//finds whether a certain concept can be attempted by student depending on status of pre-requisites
int findAvailableConcepts(int c,set<int> &concept_list)
{
	int AND=1;

	for(int i=0;i<e;i++)
	{
		if(inc_mat[c][i]==-1)
		{ 
			int OR=0;
			for(int j=0;j<v;j++)
			{
				if(inc_mat[j][i]==1){
					if(concept_state[j]==1)
					{
						OR=1;
						break;
					}
					if(concept_state[j]==-1)
						OR=-1;
				}
			}
			if(OR==0)
			{
				for(int j=0;j<v;j++)
				{
					if(inc_mat[j][i]==1 && concept_state[j]==0){
						concept_list.insert(j);
					}
				}
			}
			if(OR==0)
				AND=0;
			else if(OR==-1 && AND!=0)
				AND=-1;
		}
	}
	return AND;
}
void conceptHandler()
{
	string s;
	cin>>s;
	if(s=="list")
	{
		for(int i=0;i<v;i++){
			cout<<concepts_name[i]<<" -> ";
			if(concept_state[i]==-1)
				cout<<"unknown\n";
			else if(concept_state[i]==0)
				cout<<"failed\n";
			else
				cout<<"passed\n";
		}
		return;
	}
	int c;
	cin>>c;
	if(s=="pass")
		concept_state[c]=1;
	else if(s=="fail")
		concept_state[c]=0;
	else if(s=="attempt"){
		set<int> concept_list;
		int result=findAvailableConcepts(c,concept_list);
		if(result==-1)
			cout<<"Some concept states are unknown\n";
		else if(result==1)
			cout<<"You can attempt "<<concepts_name[c]<<"\n";
		else
		{
			cout<<"You need to pass some of these concepts:\n";
			for(auto it:concept_list)
				cout<<concepts_name[it]<<"\n";
		}
	}
	else
		cout<<"Invalid command\n";
}
int main()
{	
	ifstream file;
	file.open("input.txt");

	file>>v>>e;
	concepts_name.resize(v);
	inc_mat.resize(v,vector<int>(e));
	concept_state.resize(v,-1); //set all as unknown
		
	//Reading name of all concepts
	getline(file,concepts_name[0]);
	for(int i=0;i<v;i++)
		getline(file,concepts_name[i]);
	
	//Reading incidence matrix
	for(int i=0;i<v;i++)
	{
		for(int j=0;j<e;j++)
			file>>inc_mat[i][j];
	}
	file.close();

	string s;
	while(1)
	{
		cin>>s;
		if(s=="exit")
			break;
		if(s=="concept")
		{
			conceptHandler();
		}
		cout<<"\n";
	}
}
