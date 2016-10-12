#ifndef MAZE_H
#define MAZE_H
#include "Cell.h"
#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

class Cell;

class Maze
{
private:
    std::vector< std::vector<Cell> > maze;
    size_t width;
    size_t height;
    std::pair< Cell* , Cell* > start_end;
public:
    Maze(char* filepath, std::pair<int, int> Mitko, std::pair<int, int> end);

    size_t get_width() const { return width; }
    size_t get_height() const { return height; }
    Cell* get_at(int x, int y) { return &maze[x][y]; }
    const Cell* get_start() { return start_end.first;}
    const Cell* get_end() { return start_end.second; }
private:
    bool read_maze(char* filepath);
    bool read_one_line(std::ifstream& reader, std::vector<Cell>& result, size_t count);
    bool solve_maze();
    bool find_start_end_positions();
    void print_path(Cell* current);
};

#endif // MAZE_H
