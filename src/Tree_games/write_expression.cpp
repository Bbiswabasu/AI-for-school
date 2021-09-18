#include <iostream>
#include <stack>
#include "dag_generator.h"
#include "write_expression.h"
#include "bddObj.h"

using namespace std;

extern void bddToDot(bddMgr &mgr, BDD f, int num_vars, FILE *fp_dot, int debug = 0, int verbose = 0);

WriteExpression::WriteExpression() {}

string WriteExpression::get_syntax_error() const { return syntax_error; }

BDD WriteExpression::buildBDDFromAdj(int node, bddMgr &mgr, vector<BDD> &vars)
{
    if (DAGGenerator::adj[node].size() == 0)
    {
        return vars[DAGGenerator::content[node][0] - 'a'];
    }
    if (DAGGenerator::adj[node].size() == 1)
    {
        return ~buildBDDFromAdj(DAGGenerator::adj[node][0], mgr, vars);
    }
    BDD left = buildBDDFromAdj(DAGGenerator::adj[node][0], mgr, vars);
    BDD right = buildBDDFromAdj(DAGGenerator::adj[node][1], mgr, vars);
    BDD ans;
    if (DAGGenerator::content[node] == "&")
        ans = (left & right);
    else if (DAGGenerator::content[node] == "|")
        ans = (left | right);
    else if (DAGGenerator::content[node] == "=>")
        ans = ((~left) | right);
    else if (DAGGenerator::content[node] == "<=>")
        ans = (((~left) & (~right)) | (left & right));
    return ans;
}

BDD WriteExpression::buildBDDFromStr(string &s, bddMgr &mgr, vector<BDD> &vars)
{
    stack<char> oprtr;
    stack<BDD> operand;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
            continue;
        if (s[i] == '(' || s[i] == '|' || s[i] == '&' || s[i] == '~')
            oprtr.push(s[i]);
        else if (s[i] == '=' && i + 1 < s.size() && s[i + 1] == '>')
        {
            oprtr.push('=');
            i++;
        }
        else if (s[i] == '<' && i + 2 < s.size() && s[i + 1] == '=' && s[i + 2] == '>')
        {
            oprtr.push('<');
            i += 2;
        }
        else if (s[i] >= 'a' && s[i] <= 'a' + DAGGenerator::num_vars - 1)
            operand.push(vars[s[i] - 'a']);
        else if (s[i] == ')')
        {
            BDD right = operand.top();
            operand.pop();
            if (oprtr.top() == '(')
                operand.push(right);
            else if (oprtr.top() == '~')
            {
                operand.push(~right);
                oprtr.pop();
                oprtr.pop();
            }
            else
            {
                BDD left = operand.top();
                operand.pop();
                if (oprtr.top() == '&')
                    operand.push(left & right);
                else if (oprtr.top() == '|')
                    operand.push(left | right);
                else if (oprtr.top() == '=')
                    operand.push((~left) | right);
                else if (oprtr.top() == '<')
                    operand.push(((~left) & (~right)) | (left & right));
                oprtr.pop();
                oprtr.pop();
            }
        }
    }
    return operand.top();
}

bool WriteExpression::check(string s)
{
    //Build the actual BDD
    bddMgr mgr_actual(0, 0);
    vector<BDD> vars_actual;
    for (int i = 0; i < DAGGenerator::num_vars; i++)
    {
        vars_actual.push_back(mgr_actual.bddVar());
    }

    BDD exp_actual = buildBDDFromAdj(0, mgr_actual, vars_actual);
    FILE *fp_dot = fopen("bdd_actual.txt", "w");
    bddToDot(mgr_actual, exp_actual, DAGGenerator::num_vars, fp_dot);
    fclose(fp_dot);

    //Build BDD of student's expression
    bddMgr mgr_student(0, 0);
    vector<BDD> vars_student;
    for (int i = 0; i < DAGGenerator::num_vars; i++)
    {
        vars_student.push_back(mgr_student.bddVar());
    }

    BDD exp_student = buildBDDFromStr(s, mgr_student, vars_student);
    fp_dot = fopen("bdd_student.txt", "w");
    bddToDot(mgr_student, exp_student, DAGGenerator::num_vars, fp_dot);
    fclose(fp_dot);

    //Check if BDDs are same
    FILE *f1 = fopen("bdd_actual.txt", "r");
    FILE *f2 = fopen("bdd_student.txt", "r");
    char ch1, ch2;
    do
    {
        ch1 = fgetc(f1);
        ch2 = fgetc(f2);
        if (ch1 != ch2)
            return 0;
    } while (ch1 != EOF && ch2 != EOF);
    fclose(f1);
    fclose(f2);
    return (ch1 == EOF && ch2 == EOF);
}

bool WriteExpression::syntax_check(string s)
{
    bool bracketed = 0;
    if (s[0] != '(')
    {
        bracketed = 1;
        s = "(" + s + ")";
    }
    //check proper paranthesis and valid characters
    int st = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
            continue;
        if (s[i] == '(')
            st++;
        else if (s[i] == ')')
            st--;
        else if (!(s[i] == '~' || s[i] == '|' || s[i] == '&' ||
                   (i < s.size() - 1 && s[i] == '=' && s[i + 1] == '>') ||
                   (i < s.size() - 2 && s[i] == '<' && s[i + 1] == '=' && s[i + 2] == '>') ||
                   (s[i] >= 'a' && s[i] <= 'a' + DAGGenerator::num_vars - 1)))
        {
            syntax_error = "Invalid character at position : " + to_string(i + 1 - bracketed);
            return 0;
        }
        if (s[i] == '=')
            i++;
        else if (s[i] == '<')
            i += 2;
        if (st < 0)
        {
            syntax_error = "Expression is not properly parenthesized";
            return 0;
        }
    }
    if (st != 0)
    {
        syntax_error = "Expression is not properly parenthesized";
        return 0;
    }

    //check proper operator and operand
    stack<pair<char, int>> oprtr;
    stack<pair<char, int>> operand;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
            continue;
        if (s[i] == '(' || s[i] == '|' || s[i] == '&' || s[i] == '~')
            oprtr.push({s[i], i});
        else if (s[i] == '=' && i + 1 < s.size() && s[i + 1] == '>')
        {
            oprtr.push({'=', i});
            i++;
        }
        else if (s[i] == '<' && i + 2 < s.size() && s[i + 1] == '=' && s[i + 2] == '>')
        {
            oprtr.push({'<', i});
            i += 2;
        }
        else if (s[i] >= 'a' && s[i] <= 'a' + DAGGenerator::num_vars - 1)
            operand.push({'z', i});
        else if (s[i] == ')')
        {
            if (operand.empty())
            {
                syntax_error = "Operand missing";
                return 0;
            }
            auto right = operand.top();
            operand.pop();

            if (oprtr.top().first == '(')
                operand.push(right);
            else if (oprtr.top().first == '~')
            {
                operand.push(right);
                oprtr.pop();
                if (oprtr.top().first != '(')
                {
                    syntax_error = "Subexpressions are not properly parenthesized";
                    return 0;
                }
                oprtr.pop();
            }
            else
            {
                if (operand.empty())
                {
                    syntax_error = "Operand missing";
                    return 0;
                }
                auto left = operand.top();
                operand.pop();
                auto op = oprtr.top();
                oprtr.pop();
                if (op.first != '|' && op.first != '&' && op.first != '=' && op.first != '<')
                {
                    syntax_error = "Operator missing";
                    return 0;
                }
                if (!(right.second > op.second && left.second < op.second))
                {
                    syntax_error = "Operator missing";
                    return 0;
                }
                operand.push(left);
                if (oprtr.top().first != '(')
                {
                    syntax_error = "Subexpressions are not properly parenthesized";
                    return 0;
                }
                oprtr.pop();
            }
        }
    }
    syntax_error = "No syntax error";
    return 1;
}
void WriteExpression::startGame()
{
    cout << "Write expression at node 0 : ";
    string s;
    getline(cin, s);
    getline(cin, s);
    if (!syntax_check(s))
    {
        cout << syntax_error << "\n";
        return;
    }
    cout << syntax_error << "\n";
    if (check(s))
        cout << "CORRECT\n";
    else
        cout << "WRONG\n";
}