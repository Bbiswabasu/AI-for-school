#include <bits/stdc++.h>
#include "dag_generator.h"
#include "write_expression.h"
#include "bddObj.h"

using namespace std;

vector<BDD> vars;

extern void bddToDot(bddMgr& mgr, BDD f, int num_vars, FILE* fp_dot, int debug = 0, int verbose = 0);

BDD WriteExpression::build(int node, bddMgr& mgr)
{
    if(adj[node].size()==0)
    {
        vars.push_back(mgr.bddVar());
        return vars[vars.size()-1];
    }
    if(adj[node].size()==1)
    {
        return ~build(adj[node][0],mgr);
    }
    BDD left=build(adj[node][0],mgr);
    BDD right=build(adj[node][1],mgr);
    BDD ans;
    if(content[node]=="&")
		ans=(left & right);
	else if(content[node]=="|")
		ans=(left | right);
	else if(content[node]=="=>")
		ans=((~left) | right);
	else if(content[node]=="<=>")
		ans=(((~left) & (~right)) | (left & right));
    return ans;	
}

void WriteExpression::startGame()
{
    cout<<"Write expression at node 0 : ";
    string s;
    cin>>s;
    bddMgr mgr(0,0);
    BDD exp=build(0,mgr);
    FILE *fp_dot=fopen("bddOutput.txt","w");    
    bddToDot(mgr, exp, num_vars, fp_dot);
    fclose(fp_dot);
}