#include <iostream>
#include "crossword_generator.h"
#include "CSPify.h"
#include "find_missing_arc.h"
#include "more_constraint_node.h"
#include "arc_consistency.h"
#include "crossword_game_menu.h"
#include "find_crossword_nodes.h"
#include "draw_crossword_graph.h"
#include "crossword_backtracking_tree.h"
using namespace std;

void CrosswordGameMenu::showMenu()
{
	CrosswordGenerator cross_gen;
	cout << "Enter size of crossword : ";
	cin >> CrosswordGenerator::grid_size;
	cross_gen.do_all_tasks();

	// string s[5]={"#....",".#.#.",".....",".####","....."}; // to generate grid manually
	// for(int i=1;i<=CrosswordGenerator::grid_size;i++)
	// for(int j=1;j<=CrosswordGenerator::grid_size;j++)
	// CrosswordGenerator::grid[i][j]=s[i-1][j-1];

	CSPify csp_obj;
	csp_obj.do_all_tasks();

	cout << "1. Find Nodes in Crossword\n";
	cout << "2. Find Missing Arc\n";
	cout << "3. Draw Constraint Graph\n";
	cout << "4. Find more constraint node\n";
	cout << "5. Arc consistency\n";
	cout << "6. Backtracking Tree\n";
	while (1)
	{
		cout << "Which game? ";
		int tmp;
		cin >> tmp;
		cross_gen.print_grid();
		switch (tmp)
		{
		case 1:
		{
			FindCrosswordNodes find_nodes;
			find_nodes.startGame();
			break;
		}

		case 2:
			FindMissingArc miss_arc;
			miss_arc.startGame();
			break;

		case 3:
		{
			DrawCrosswordGraph draw_graph;
			draw_graph.startGame();
			break;
		}

		case 4:
			MoreConstraintNode more_cons;
			more_cons.startGame();
			break;

		case 5:
		{
			ArcConsistency arc_con;
			arc_con.startGame();
			break;
		}

		case 6:
		{
			CrosswordBacktrackingTree cross_back;
			cross_back.startGame();
			break;
		}

		default:
			return;
		}
	}
}