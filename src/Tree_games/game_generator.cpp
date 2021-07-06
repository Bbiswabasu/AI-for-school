//generates games based on parameters

#include <bits/stdc++.h>
#include "dag_generator.h"
#include "expression_evaluation.h"
#include "match_expression_with_node.h"
#include "fill_missing_operators.h"
#include "write_expression.h"

using namespace std;

int main()
{
	DAGGenerator dag_gen;
	cout<<"No of variables : ";
	cin>>DAGGenerator::num_vars;
	cout<<"No of nodes : ";
	cin>>DAGGenerator::num_nodes;
	dag_gen.init();
	dag_gen.generate_dag();
	dag_gen.assign_content();
	dag_gen.display_dag(); 
	dag_gen.assign_values();
	cout<<"1. Expression Evaluation\n";
	cout<<"2. Match Expression With Node\n";
	cout<<"3. Fill missing operators\n";
	cout<<"4. Write Expression\n";
	
	while(1)
	{
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
			{
				MatchExpression mat;
				mat.startGame();
			}
			break;

			case 3:
			MissingOperators mop;
			mop.startGame();
			break; 

			case 4:
			WriteExpression write;
			write.startGame();
			break;

			default:
			return 0;
		}
	}
}