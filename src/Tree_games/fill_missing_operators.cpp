#include <iostream>
#include <algorithm>
#include "fill_missing_operators.h"
#include "expression_evaluation.h"
#include "dag_generator.h"

using namespace std;

void MissingOperators::startGame()
{
	ExpressionEvaluation exp;
	exp.evaluate(0);
	vector<int> values_mem=DAGGenerator::values; //Store for checking correctness of student's solution
	int num_operator=DAGGenerator::adj.size()-DAGGenerator::num_vars;
	vector<int> index;
	for(int i=0;i<DAGGenerator::adj.size();i++)
		index.push_back(i);
	random_shuffle(index.begin(),index.end());
	for(int i=0,ctr=0;ctr!=num_operator/2;i++)
	{
		if(!isalpha(DAGGenerator::content[i][0])){
			DAGGenerator::content[i]="?";
			ctr++;
		}
	}

	DAGGenerator dag_gen;
	dag_gen.display_dag();
	cout<<"Fill missing operators such that the given DAGGenerator::values are satisfied : \n";
	for(int i=0;i<num_operator/2;i++)
	{
		int node; string op;
		cin>>node>>op;
		DAGGenerator::content[node]=op;
	}
	new(&exp) ExpressionEvaluation();
	exp.evaluate(0);
	bool wrong=0;
	for(int i=0;i<DAGGenerator::adj.size();i++)
	{
		if(values_mem[i]!=DAGGenerator::values[i])
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