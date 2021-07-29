#include <vector>
#include <string>
using namespace std;

class DAGGenerator
{
public:
    static int num_vars;
    static int num_nodes;
    int id; //id of current node to be added
    int var_name;

    static vector<vector<int>> adj;
    static vector<string> content;
    static vector<int> values;
    static vector<string> operators;
    static vector<int> indeg;
    static vector<string> expressions;

    void init();
    int random(int, int);
    void generate_dag();
    void assign_content();
    void assign_values();
    void display_dag();
    void do_all_tasks();
};