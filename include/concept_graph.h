#include <vector>
#include <string>
#include <set>
using namespace std;

class ConceptGraph
{
public:
    vector<vector<vector<int>>> graph;
    vector<int> completed;
    vector<int> status;

    vector<int> get_status() const;
    vector<int> get_completed() const;
    
    ConceptGraph();
    void init();
    void compute_individual_status(int);
    void compute_status();
    void mark_complete(int);
    void showMenu();
};