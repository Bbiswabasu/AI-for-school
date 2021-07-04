#include <bits/stdc++.h>
#include "dag_generator.h"
#include "write_expression.h"
#include "bddObj.h"

using namespace std;

extern void bddToDot(bddMgr& mgr, BDD f, int num_vars, FILE* fp_dot, int debug = 0, int verbose = 0);

BDD WriteExpression::build(int node, bddMgr& mgr,vector<BDD>& vars)
{
    if(adj[node].size()==0)
    {
        return vars[content[node][0]-'a'];
    }
    if(adj[node].size()==1)
    {
        return ~build(adj[node][0],mgr,vars);
    }
    BDD left=build(adj[node][0],mgr,vars);
    BDD right=build(adj[node][1],mgr,vars);
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
    vector<BDD> vars_actual;
    for(int i=0;i<num_vars;i++)
    {
        vars_actual.push_back(mgr.bddVar());
    }
    
    BDD exp_actual=build(0,mgr,vars_actual);
    FILE *fp_dot=fopen("bddOutput.txt","w");    
    bddToDot(mgr, exp_actual, num_vars, fp_dot);
    fclose(fp_dot);
}