#include<bits/stdc++.h>
#include "crossword_generator.h"
#include "CSPify.h"
#include "find_missing_arc.h"
#include "more_constraint_node.h"
#include "arc_consistency.h"
#include "crossword_game_menu.h"
using namespace std;

void CrosswordGameMenu::showMenu() 
{
	CrosswordGenerator cross_gen;
	cout<<"Enter size of crossword : ";
	cin>>CrosswordGenerator::grid_size;
	cross_gen.init();
	cross_gen.distribution();
	cross_gen.form_grid();
	cross_gen.adjust();
	
	cross_gen.print_grid();

	CSPify csp_obj;
	csp_obj.init();
	csp_obj.cspify();
	csp_obj.print_graph();

	cout<<"1. Find Missing Arc\n";
	cout<<"2. Find more constraint node\n";
	cout<<"3. Arc consistency\n";
	while(1)
	{
		cout<<"Which game? ";
		int tmp;
		cin>>tmp;
		cross_gen.print_grid();
		switch(tmp)
		{
			case 1:
			FindMissingArc miss_arc;
			miss_arc.startGame();
			break;

			case 2:
			MoreConstraintNode more_cons;
			more_cons.startGame();
			break;

			case 3:{
				ArcConsistency arc_con;
				arc_con.startGame();
				break;
			}
 
			default:
			return;
		}
	}
}