//generates games based on parameters

#include <bits/stdc++.h>
#include "tree_generator.h"
#include "expression_evaluation.h"
#include "match_expression_with_node.h"

using namespace std;

int main()
{
	cout<<"No of variables : ";
	cin>>num_vars;
	init();
	generate_tree();
	assign_content();
	display_tree(); 
	assign_values();
	cout<<"1. Expression Evaluation\n";
	cout<<"2. Match Expression With Node\n";
	cout<<"Which game? ";
	int tmp;
	cin>>tmp;
	switch(tmp)
	{
		case 1:
		ExpressionEvaluation exp;
		exp.startGame();
		break;

		case 2:
		MatchExpression mat;
		mat.startGame();
		break;
	}
}