#include <bits/stdc++.h>
#include "fill_missing_operators.h"
#include "expression_evaluation.h"
#include "dag_generator.h"

using namespace std;

void MissingOperators::startGame()
{
	ExpressionEvaluation exp;
	exp.evaluate(0);
	vector<int> values_mem=values; //Store for checking correctness of student's solution
	int num_operator=adj.size()-num_vars;
	vector<int> index;
	for(int i=0;i<adj.size();i++)
		index.push_back(i);
	random_shuffle(index.begin(),index.end());
	for(int i=0,ctr=0;ctr!=num_operator/2;i++)
	{
		if(!isalpha(content[i][0])){
			content[i]="?";
			ctr++;
		}
	}
	display_dag();
	cout<<"Fill missing operators such that the given values are satisfied : \n";
	for(int i=0;i<num_operator/2;i++)
	{
		int node; string op;
		cin>>node>>op;
		content[node]=op;
	}
	new(&exp) ExpressionEvaluation();
	exp.evaluate(0);
	bool wrong=0;
	for(int i=0;i<adj.size();i++)
	{
		if(values_mem[i]!=values[i])
		{
			wrong=1;
			break;
		}
	}
	if(wrong)
		cout<<"WRONG\n";
	else
		cout<<"CORRECT\n";
}