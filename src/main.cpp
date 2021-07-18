#include <bits/stdc++.h>
#include "tree_game_menu.h"
#include "crossword_game_menu.h"
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
        else
            break;
    }   
}