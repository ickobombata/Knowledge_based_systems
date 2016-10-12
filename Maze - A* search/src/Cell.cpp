#include "Cell.h"

Cell::Cell(char symbol, Maze* maze, std::pair<int, int> position)
    : symbol(symbol), maze(maze), position(position), parent(NULL), priority(0), cost_till_now(0), visited(false)
{}

void Cell::get_neighbours(std::queue< Cell* >& result, bool walkable)
{
    walkable = !walkable;
    int x = position.first;
    int y = position.second;

    if(exist_neighbour(x, y+1, walkable))
        result.push(maze->get_at(x, y+1));
    if(exist_neighbour(x, y-1, walkable))
        result.push(maze->get_at(x, y-1));
    if(exist_neighbour(x+1, y-1, walkable))
        result.push(maze->get_at(x+1, y-1));
    if(exist_neighbour(x+1, y, walkable))
        result.push(maze->get_at(x+1, y));
    if(exist_neighbour(x+1, y+1, walkable))
        result.push(maze->get_at(x+1, y+1));
    if(exist_neighbour(x-1, y-1, walkable))
        result.push(maze->get_at(x-1, y-1));
    if(exist_neighbour(x-1, y, walkable))
        result.push(maze->get_at(x-1, y));
    if(exist_neighbour(x-1, y+1, walkable))
        result.push(maze->get_at(x-1, y+1));
}

bool Cell::exist_neighbour(int x, int y, bool walkable)
{
    if(x >= 0 && x < maze->get_width() && y >= 0 && y < maze->get_height())
        if((maze->get_at(x, y)->get_symbol() != 'N') && maze->get_at(x, y)->is_visited() == walkable)
        {
            //std::cout << "WALKABLE IS " << x << " " << y << " becaulse N != '" << maze[x][y].symbol << "' And visited = " <<
            //maze[x][y].visited<< std::endl;
            return true;
        }
    return false;
}
double Cell::calculate_distance(const Cell* to)
{
    double first = std::abs(to->position.first - position.first);
    double second = std::abs(to->position.second - position.second);

    if(first > second)
        return first - second + second * 1.5 ;
    else
        return second - first + first * 1.5 ;
}
void Cell::calculate_priority(Cell* parent)
{
    float addition = 2;
    if(parent->get_symbol() != '~')
        addition = ((parent->get_position().first != position.first && parent->get_position().second != position.second)? 1.5 : 1);

    this->parent = parent;
    const Cell* end_point = maze->get_end();
    set_cost(parent->get_cost() + addition);

    set_priority(get_cost() + calculate_distance(end_point));
}
void Cell::set_cost(double cost_till_now)
{
    this->cost_till_now = (cost_till_now > 0)? cost_till_now : 0;
}
