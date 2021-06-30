//generates games based on parameters

#include <bits/stdc++.h>
#include "dag_generator.h"
#include "expression_evaluation.h"
#include "match_expression_with_node.h"
#include "fill_missing_operators.h"

using namespace std;

int main()
{
	cout<<"No of variables : ";
	cin>>num_vars;
	cout<<"No of nodes : ";
	cin>>num_nodes;
	init();
	generate_dag();
	assign_content();
	display_dag(); 
	assign_values();
	cout<<"1. Expression Evaluation\n";
	cout<<"2. Match Expression With Node\n";
	cout<<"3. Fill missing operators\n";
	cout<<"Which game? ";
	int tmp;
	cin>>tmp;
	switch(tmp)
	{
		case 1:
		{
			ExpressionEvaluation exp;
			exp.startGame();
		}
		break;

		case 2:
		MatchExpression mat;
		mat.startGame();
		break;

		case 3:
		MissingOperators mop;
		mop.startGame();
		break; 
	}
}