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
    static vector<int> depth;

    int get_num_vars() const;
    void set_num_vars(int);
    int get_num_nodes() const;
    void set_num_nodes(int);
    vector<vector<int>> get_adj() const;
    vector<string> get_content() const;
    vector<int> get_values() const;
    vector<string> get_operators() const;
    vector<int> get_indeg() const;
    vector<string> get_expressions() const;
    vector<int> get_depth() const;

    DAGGenerator();
    void init();
    int random(int, int);
    void generate_dag();
    void assign_content();
    void assign_values();
    void display_dag();
    void compute_depth();
    void do_all_tasks();
};