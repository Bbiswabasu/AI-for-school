#include <bits/stdc++.h>
using namespace std;

extern vector<vector<int>> adj;
extern vector<string> content;
extern vector<int> values;
extern int num_vars;

void init();
void generate_tree();
void assign_content();
void assign_values();
void display_tree();
void display_expression();
