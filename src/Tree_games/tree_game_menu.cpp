//generates games based on parameters

#include <iostream>
#include "dag_generator.h"
#include "expression_evaluation.h"
#include "match_expression_with_node.h"
#include "fill_missing_content.h"
#include "write_expression.h"
#include "tree_game_menu.h"

using namespace std;

void TreeGameMenu::showMenu()
{
	DAGGenerator dag_gen;
	cout << "No of variables : ";
	cin >> DAGGenerator::num_vars;
	cout << "No of nodes : ";
	cin >> DAGGenerator::num_nodes;
	dag_gen.do_all_tasks();
	cout << "1. Expression Evaluation\n";
	cout << "2. Match Expression With Node\n";
	cout << "3. Fill missing operators\n";
	cout << "4. Write Expression\n";

	while (1)
	{
		cout << "Which game? ";
		int tmp;
		cin >> tmp;
		switch (tmp)
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
		{
			MissingContent mop;
			mop.startGame();
		}
		break;

		case 4:
		{
			WriteExpression write;
			write.startGame();
		}
		break;

		default:
			return;
		}
	}
}