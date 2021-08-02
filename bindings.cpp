#include <emscripten/bind.h>
#include "dag_generator.h"
#include "expression_evaluation.h"
#include "match_expression_with_node.h"
#include "crossword_generator.h"

#include <string>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(tree_games)
{
    register_vector<string>("VectorString");
    register_vector<int>("VectorInt");
    register_vector<vector<int>>("VectorVectorInt");

    class_<DAGGenerator>("DAGGenerator")
        .constructor<>()
        .function("init", &DAGGenerator::init)
        .function("generate_dag", &DAGGenerator::generate_dag)
        .function("assign_content", &DAGGenerator::assign_content)
        .function("assign_values", &DAGGenerator::assign_values)
        .function("display_dag", &DAGGenerator::display_dag)
        .function("compute_graph_layout", &DAGGenerator::compute_graph_layout)
        .function("do_all_tasks", &DAGGenerator::do_all_tasks)
        .property("num_vars", &DAGGenerator::get_num_vars, &DAGGenerator::set_num_vars)
        .property("num_nodes", &DAGGenerator::get_num_nodes, &DAGGenerator::set_num_nodes)
        .property("adj", &DAGGenerator::get_adj)
        .property("content", &DAGGenerator::get_content)
        .property("values", &DAGGenerator::get_values)
        .property("expressions", &DAGGenerator::get_expressions)
        .property("x_coor", &DAGGenerator::get_x_coor)
        .property("y_coor", &DAGGenerator::get_y_coor)
        .property("edge_carvature", &DAGGenerator::get_edge_carvature);

    class_<MatchExpression>("MatchExpression")
        .constructor<>()
        .function("init", &MatchExpression::init)
        .function("compute_expressions", &MatchExpression::compute_expressions);

    class_<ExpressionEvaluation>("ExpressionEvaluation")
        .constructor<>()
        .function("init", &ExpressionEvaluation::init)
        .function("evaluate", &ExpressionEvaluation::evaluate)
        .property("order_of_evaluation", &ExpressionEvaluation::get_order_of_evaluation);
};

EMSCRIPTEN_BINDINGS(crossword_games)
{
    register_vector<char>("VectorChar");
    register_vector<vector<char>>("VectorVectorChar");
    class_<CrosswordGenerator>("CrosswordGenerator")
        .constructor<>()
        .function("init", &CrosswordGenerator::init)
        .function("do_all_tasks", &CrosswordGenerator::do_all_tasks)
        .property("grid_size", &CrosswordGenerator::get_grid_size, &CrosswordGenerator::set_grid_size)
        .property("grid", &CrosswordGenerator::get_grid);        
};