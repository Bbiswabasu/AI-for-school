#include <bits/stdc++.h>
using namespace std;

extern int num_vars; 
extern int num_nodes;

extern vector<vector<int>> adj;
extern vector<string> content; 
extern vector<int> values;
extern vector<string> operators;

void init();
void generate_dag();
void assign_content();
void assign_values();
void display_dag();
void display_expression();