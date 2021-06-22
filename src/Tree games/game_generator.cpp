//generates games based on parameters

#include <bits/stdc++.h>
#include "tree_generator.h"
#include "expression_evaluation.h"

using namespace std;

int main()
{
	cout<<"No of variables : ";
	cin>>num_vars;
	init();
	generate_tree();
	assign_content();
	display_tree(); 
	cout<<"Evaluating games? ";
	int tmp;
	cin>>tmp;
	if(tmp)
	{
		assign_values();
		cout<<"How many variables & operators remain empty? ";
		int var,op;
		cin>>var>>op;
		if(var==0 && op==0)
		{
			ExpressionEvaluation obj;
			obj.startGame();
		}
	}
	else
	{

	}
}