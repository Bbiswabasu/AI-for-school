#include "dag_generator.h"
#include "expression_evaluation.h"
#include "match_expression_with_node.h"
#include "fill_missing_content.h"
#include "write_expression.h"
#include "crossword_generator.h"
#include "CSPify.h"
#include "find_crossword_nodes.h"
#include "node_consistency.h"
#include "find_missing_arc.h"
#include "draw_crossword_graph.h"
#include <emscripten/bind.h>

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
        .function("restore_dag", &DAGGenerator::restore_dag)
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

    class_<ExpressionEvaluation>("ExpressionEvaluation")
        .constructor<>()
        .function("init", &ExpressionEvaluation::init)
        .function("evaluate", &ExpressionEvaluation::evaluate)
        .property("order_of_evaluation", &ExpressionEvaluation::get_order_of_evaluation)
        .property("exp_to_display", &ExpressionEvaluation::get_exp_to_display);

    class_<MatchExpression>("MatchExpression")
        .constructor<>()
        .function("init", &MatchExpression::init)
        .function("restore_exp", &MatchExpression::restore_exp)
        .function("compute_expressions", &MatchExpression::compute_expressions)
        .function("preprocessing", &MatchExpression::preprocessing)
        .function("add_response", &MatchExpression::add_response)
        .function("check", &MatchExpression::check)
        .property("indices", &MatchExpression::get_indices)
        .property("exp_to_display", &MatchExpression::get_exp_to_display)
        .property("correct_response", &MatchExpression::get_correct_response)
        .property("wrong_response", &MatchExpression::get_wrong_response)
        .property("correct_answers", &MatchExpression::get_correct_answers);

    class_<MissingContent>("MissingContent")
        .constructor<>()
        .function("backup_data", &MissingContent::backup_data)
        .function("restore_data", &MissingContent::restore_data)
        .function("miss_content", &MissingContent::miss_content)
        .function("change_content", &MissingContent::change_content)
        .function("check", &MissingContent::check)
        .property("cnt_op", &MissingContent::get_cnt_op, &MissingContent::set_cnt_op)
        .property("cnt_var", &MissingContent::get_cnt_var, &MissingContent::set_cnt_var);

    class_<WriteExpression>("WriteExpression")
        .constructor<>()
        .function("syntax_check", &WriteExpression::syntax_check)
        .function("check", &WriteExpression::check)
        .property("syntax_error", &WriteExpression::get_syntax_error);
};

EMSCRIPTEN_BINDINGS(crossword_games)
{
    register_vector<char>("vector<char>");
    register_vector<string>("vector<string>");
    register_vector<int>("vector<int>");
    register_vector<vector<char>>("vector<vector<char>>");
    register_vector<pair<int, int>>("vector<pair<int, int>>");
    register_vector<pair<pair<int, int>, int>>("vector<pair<pair<int, int>, int>>");
    register_vector<pair<pair<int, int>, char>>("vector<pair<pair<int, int>, char>>");
    register_vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>>("vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>>");

    class_<std::pair<int, int>>("pair<int, int>")
        .property("first", &std::pair<int, int>::first)
        .property("second", &std::pair<int, int>::second);

    class_<std::pair<pair<int, int>, int>>("pair<pair<int, int>, int>")
        .property("first", &std::pair<pair<int, int>, int>::first)
        .property("second", &std::pair<pair<int, int>, int>::second);

    class_<std::pair<pair<int, int>, char>>("pair<pair<int, int>, char>")
        .property("first", &std::pair<pair<int, int>, char>::first)
        .property("second", &std::pair<pair<int, int>, char>::second);

    class_<std::pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>>("pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>")
        .property("first", &std::pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>::first)
        .property("second", &std::pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>::second);

    class_<CrosswordGenerator>("CrosswordGenerator")
        .constructor<>()
        .function("restore_grid", &CrosswordGenerator::restore_grid)
        .function("init", &CrosswordGenerator::init)
        .function("do_all_tasks", &CrosswordGenerator::do_all_tasks)
        .property("grid_size", &CrosswordGenerator::get_grid_size, &CrosswordGenerator::set_grid_size)
        .property("grid", &CrosswordGenerator::get_grid);

    class_<CSPify>("CSPify")
        .constructor<>()
        .function("do_all_tasks", &CSPify::do_all_tasks)
        .property("nodes", &CSPify::get_nodes);

    class_<FindCrosswordNodes>("FindCrosswordNodes")
        .constructor<>()
        .function("check", &FindCrosswordNodes::check)
        .function("add_node", &FindCrosswordNodes::add_node)
        .property("nodes_across", &FindCrosswordNodes::get_nodes_across)
        .property("nodes_down", &FindCrosswordNodes::get_nodes_down)
        .property("missed_nodes", &FindCrosswordNodes::get_missed_nodes)
        .property("wrong_nodes", &FindCrosswordNodes::get_wrong_nodes)
        .property("correct_nodes", &FindCrosswordNodes::get_correct_nodes);

    class_<NodeConsistency>("NodeConsistency")
        .constructor<>()
        .function("init", &NodeConsistency::init)
        .function("restore_bag", &NodeConsistency::restore_bag)
        .function("choose", &NodeConsistency::choose)
        .function("add_response", &NodeConsistency::add_response)
        .function("check", &NodeConsistency::check)
        .property("shuffled_bag_ind", &NodeConsistency::get_shuffled_bag_ind)
        .property("shuffled_bag", &NodeConsistency::get_shuffled_bag)
        .property("result", &NodeConsistency::get_result);

    class_<FindMissingArc>("FindMissingArc")
        .constructor<>()
        .function("choose_arc", &FindMissingArc::choose_arc)
        .function("check", &FindMissingArc::check)
        .property("arcs_to_display", &FindMissingArc::get_arcs_to_display)
        .property("answer", &FindMissingArc::get_answer);

    class_<DrawCrosswordGraph>("DrawCrosswordGraph")
        .constructor<>()
        .function("init", &DrawCrosswordGraph::init)
        .function("check", &DrawCrosswordGraph::check)
        .function("add_edge", &DrawCrosswordGraph::add_edge)
        .property("missed_edges", &DrawCrosswordGraph::get_missed_edges)
        .property("wrong_edges", &DrawCrosswordGraph::get_wrong_edges)
        .property("correct_edges", &DrawCrosswordGraph::get_correct_edges);
};