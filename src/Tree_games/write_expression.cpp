#include <iostream>
#include <stack>
#include "dag_generator.h"
#include "write_expression.h"
#include "bddObj.h"

using namespace std;

extern void bddToDot(bddMgr& mgr, BDD f, int num_vars, FILE* fp_dot, int debug = 0, int verbose = 0);

BDD WriteExpression::buildBDDFromAdj(int node, bddMgr& mgr,vector<BDD>& vars)
{
    if(DAGGenerator::adj[node].size()==0)
    {
        return vars[DAGGenerator::content[node][0]-'a'];
    }
    if(DAGGenerator::adj[node].size()==1)
    {
        return ~buildBDDFromAdj(DAGGenerator::adj[node][0],mgr,vars);
    }
    BDD left=buildBDDFromAdj(DAGGenerator::adj[node][0],mgr,vars);
    BDD right=buildBDDFromAdj(DAGGenerator::adj[node][1],mgr,vars);
    BDD ans;
    if(DAGGenerator::content[node]=="&")
		ans=(left & right);
	else if(DAGGenerator::content[node]=="|")
		ans=(left | right);
	else if(DAGGenerator::content[node]=="=>")
		ans=((~left) | right);
	else if(DAGGenerator::content[node]=="<=>")
		ans=(((~left) & (~right)) | (left & right));
    return ans;	
}

BDD WriteExpression::buildBDDFromStr(int i, bddMgr& mgr,vector<BDD>& vars,string &s,vector<int>& matching)
{
    if(s[i+1]=='~')
        return ~buildBDDFromStr(i+2,mgr,vars,s,matching);
    if(isalpha(s[i]))
        return vars[s[i]-'a'];
    BDD left=buildBDDFromStr(i+1,mgr,vars,s,matching);
    string op="";
    op+=s[matching[i+1]+1];
    if(op=="=")
        op+=">";
    else if(op=="<")
        op+="=>";

    BDD right=buildBDDFromStr(matching[i+1]+op.size()+1,mgr,vars,s,matching);
    BDD ans;
    
    if(op=="&")
		ans=(left & right);
	else if(op=="|")
		ans=(left | right);
	else if(op=="=>")
		ans=((~left) | right);
	else if(op=="<=>")
		ans=(((~left) & (~right)) | (left & right));
    return ans;
}

void WriteExpression::expressionParser(string& s)
{
    vector<int> matching(s.size()); //Stores index of matching ')' for each '('
    stack<int> st;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='(')
            st.push(i);
        if(s[i]==')')
        {
            matching[st.top()]=i;
            st.pop();
        }
        if(isalpha(s[i]))
            matching[i]=i;
    }

    bddMgr mgr_student(0,0);
    vector<BDD> vars_student;
    for(int i=0;i<DAGGenerator::num_vars;i++)
    {
        vars_student.push_back(mgr_student.bddVar());
    }
    
    BDD exp_student=buildBDDFromStr(0,mgr_student,vars_student,s,matching);
    FILE *fp_dot=fopen("bdd_student.txt","w");    
    bddToDot(mgr_student, exp_student, DAGGenerator::num_vars, fp_dot);
    fclose(fp_dot);
}

bool WriteExpression::verifyAnswer()
{
    FILE *f1=fopen("bdd_actual.txt","r");
    FILE *f2=fopen("bdd_student.txt","r");
    char ch1,ch2;
    do
    {
        ch1=fgetc(f1); ch2=fgetc(f2);
        if(ch1!=ch2)
            return 0;
    } while (ch1!=EOF && ch2!=EOF);
    return (ch1==EOF && ch2==EOF);
}

void WriteExpression::startGame()
{
    cout<<"Write expression at node 0 : ";
    string s;
    cin>>s;
    bddMgr mgr_actual(0,0);
    vector<BDD> vars_actual;
    for(int i=0;i<DAGGenerator::num_vars;i++)
    {
        vars_actual.push_back(mgr_actual.bddVar());
    }
    
    BDD exp_actual=buildBDDFromAdj(0,mgr_actual,vars_actual);
    FILE *fp_dot=fopen("bdd_actual.txt","w");    
    bddToDot(mgr_actual, exp_actual, DAGGenerator::num_vars, fp_dot);
    fclose(fp_dot);

    expressionParser(s);

    if(verifyAnswer())
        cout<<"CORRECT\n";
    else
        cout<<"WRONG\n";
}