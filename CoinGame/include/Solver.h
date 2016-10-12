#ifndef SOLVER_H
#define SOLVER_H
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <time.h>

typedef std::vector<bool> DATA;

struct Triplet
{
    int first;
    int second;
    int third;
};

enum Player
{
    MAX,
    MIN
};
/// the solver has a tree
class Solver
{
private:
    unsigned long N;
    struct Node
    {
        static unsigned long N;
        DATA* data;
        std::vector<Node*> children;
        size_t heuristic_coeff;

        Node(DATA* data)
        {
            this->data = data;
        };
        ~Node()
        {
            delete data;
            for(size_t i = 0; i < children.size(); ++i)
                delete children[i];
        }
        void print() const;
        void generate_children();
    };
    Node* root;
public:
    Solver(unsigned long N);
    ~Solver();
    Triplet solve();
    void print();

private:
    // a little optimization is made... I don't generate
    // the last nodes because when we have 3 last coins
    // next to each other we have a certain winner
    void generate(Node* current);
    void miniMaxStarter(int& pos, int& amount, int& points);
    int mM(Node* curretn , Player atTurn, size_t moves, int alpha, int beta);
    void print(Node* current, size_t offset);
};

#endif // SOLVER_H
