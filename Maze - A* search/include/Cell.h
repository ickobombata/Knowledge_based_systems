#ifndef CELL_H
#define CELL_H
#include <Maze.h>
#include <iostream>
#include <queue>

class Maze;
class Cell
{
private:
    Maze* maze;
    std::pair<int, int> position;
    char symbol;
    bool visited;
    double priority;
    double cost_till_now;

    Cell* parent;
public:
    Cell(char symbol, Maze* maze, std::pair<int, int> position);

    void get_neighbours(std::queue< Cell* >& result, bool walkable);
    bool exist_neighbour(int x, int y, bool walkable);
    void calculate_priority(Cell* parent) ;

    double calculate_distance(const Cell* to);


    // getters setters
    void set_symbol(char s) { symbol = s;}
    char get_symbol() { return symbol ;}
    void mark() { visited = true;}
    bool is_visited() const { return visited; }
    double get_priority() const { return priority; }
    void set_priority(double n) { this->priority = n; }
    void set_cost(double cost_till_now);
    double get_cost() const { return cost_till_now; }
    std::pair<int, int> get_position() const { return position ; }
    Cell* get_parent(){ return parent; }
    void set_parent( Cell* parent) { this->parent = parent; }
    bool is_goal() const { return symbol == 'X'; }
};

struct Compare {
  bool operator() (Cell* arg1, Cell* arg2) {
    //std::cout << "position 1:" << arg1->position.first << "," << arg1->position.second
    //          << " position 2:" << arg2->position.first << "," << arg2->position.second << std::endl;
    return arg2->get_priority() < arg1->get_priority(); //calls your operator
  }
};

#endif // CELL_H
