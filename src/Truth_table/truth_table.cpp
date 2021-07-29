#include <iostream>
#include "truth_table.h"
using namespace std;

int TruthTable::evaluateFromStr(int i,string &s,vector<int> &matching)
{

}
void TruthTable::start()
{
    cout<<"Enter expression : ";
    cin>>expression;
    num_vars=0;
    for(int i=0;i<expression.size();i++)
    {
        if(isalpha(expression[i]))
        vars.insert(expression[i]);
    }
    
}