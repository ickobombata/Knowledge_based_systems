#include "Maze.h"

Maze::Maze(char* filepath, std::pair<int, int> Mitko, std::pair<int, int> end)
{
    if(read_maze(filepath))
    {
        start_end = std::pair<Cell*, Cell*>(&maze[Mitko.second][Mitko.first], &maze[end.second][end.first]);
        start_end.first->set_symbol('M');
        start_end.second->set_symbol('X');
        if(solve_maze())
            print_path(start_end.second);
    }
}

bool Maze::read_maze(char* filepath)
{
    std::ifstream file(filepath);
    if(!file)
        return false;

    char read = ',';
    std::vector<Cell> first;

    if(read_one_line(file, first, 0))
        maze.push_back(first);
    else
        return false;

    size_t count = 1;
    while(!file.eof())
    {
        maze.push_back(std::vector<Cell>());
        bool read_correct = read_one_line(file, maze[count], count);

        if(!read_correct)
            return false;

        if(maze[count].size() == 0)
        {
            maze.pop_back();
            break;
        }
        ++count;
    }
//    for(int i = 0 ; i < maze.size(); ++i)
//    {
//        for(int j = 0 ; j < maze[0].size(); ++j)
//        {
//            maze[i][j].print();
//        }
//        std::cout << std::endl;
//    }
    this->width = maze.size();
    this->height = maze[0].size();
    return true;
}

bool Maze::read_one_line(std::ifstream& reader, std::vector<Cell>& result, size_t count)
{
    if(!reader)
        return false;
    size_t row_count = 0;
    char read = ',';
    reader.get(read);
    if(read == '\n' || reader.eof())
        return true;
    do
    {
        if(read == 'N' || read == '~' || read == ' ')
        {
            Cell temp(read, this, std::pair<int, int>(count, row_count++));
            result.push_back(temp);
        }
        else
            return false;

        reader.get(read);
        if(read != ',' && read != '\n' && !reader.eof())
            {std::cout << "EEEE" ; return false;}
        else if(read == '\n' || reader.eof())
            return true;

        reader.get(read);
    }
    while(read != '\n' && !reader.eof());

    return true;
}
bool Maze::find_start_end_positions()
{
    for(int i = 0 ;i < maze.size(); ++i)
    {
        for(int j = 0 ; j < maze[0].size(); ++j)
        {// validate
            if(maze[i][j].get_symbol() == 'M')
                start_end.first = &maze[i][j];
            else if(maze[i][j].get_symbol() == 'X')
                start_end.second = &maze[i][j];;
        }
    }
    return true;
}
void Maze::print_path(Cell* current)
{
    if(!current)
        return;

    print_path(current->get_parent());

    current->set_symbol('*');
    std::pair<int, int> position = current->get_position();
    std::cout << "(" << position.first << "," << position.second << "),";
}

bool Maze::solve_maze()
{
    // allocate everythuing needed
    std::priority_queue< Cell*, std::vector<Cell*>, Compare > p_qu;
    p_qu.push(start_end.first);
    start_end.first->mark();
    start_end.first->set_priority(0);
    std::queue< Cell* > neighbours;
    std::queue< Cell* > neighbours_of_new_Cell;
    Cell* current_cell ;

    while(!p_qu.empty())
    {
        // take the current element
        current_cell = p_qu.top();
        p_qu.pop();

        if(current_cell == start_end.second)
            return true;
        // get all neighbours that are not visited

        // add them not visited neighbours
        current_cell->get_neighbours(neighbours, true);
        while(!neighbours.empty())
        {
            Cell* before_push = neighbours.front();

            before_push->calculate_priority(current_cell);
            before_push->mark();

            p_qu.push(before_push);
            neighbours.pop();
        }
        // now we will make it if we can reach a neighbour from this point that has less distance
        // we recalculate things

        current_cell->get_neighbours(neighbours, false);
        while(!neighbours.empty())
        {
            Cell* before_push = neighbours.front();

            double distance_to_current = current_cell->calculate_distance(before_push);
            if(current_cell->get_cost() + distance_to_current < before_push->get_cost())
            {
                //before_push->set_cost(current_cell->get_cost() + current_cell->calculate_distance(before_push));
                //before_push->set_priority(before_push->get_cost() + before_push->calculate_distance(start_end.second));

                before_push->calculate_priority(current_cell);
                p_qu.push(before_push);
            }
            neighbours.pop();
        }
    }
    return false;
}



