#include <iostream>
#include "tree_game_menu.h"
#include "crossword_game_menu.h"
#include "concept_graph.h"
using namespace std;

int main()
{
    
    while(1)
    {    
        string s;
        cin>>s;
        if(s=="crossword")
        {
            CrosswordGameMenu obj;
            obj.showMenu();
        }
        else if(s=="tree")
        {
            TreeGameMenu obj;
            obj.showMenu();
        }
        else if(s=="concept")
        {
            ConceptGraph obj;
            obj.showMenu();
        }
        else if(s=="exit")
            break;
    }   
}