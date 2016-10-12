/*
    Martin Stoev
    855240
*/


#include <iostream>
#include "Maze.h"

int string_to_int(char* a)
{
    int number = 0;
    while(*a != '\0')
    {
        if(*a < '0' || *a > '9')
            throw "Bad coordiantes";
        number = number * 10 + (*a - '0');
        a++;
    }
    return number;
}

int main(int argc, char* argv[])
{
    if(argc != 6)
    {
        std::cout << "Error: arguments" ;
        return 0;
    }
    int mitko_x = string_to_int(argv[2]);
    int mitko_y = string_to_int(argv[3]);

    Maze maze(argv[1], std::pair<int, int>(mitko_x, mitko_y),
                        std::pair<int, int>(string_to_int(argv[4]), string_to_int(argv[5])));

    return 0;
}
