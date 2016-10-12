#include <iostream>
#include "Solver.h"
///
/// Мартин Стоев
/// Фн: 855240
/// Информационни системи
///
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
    if(argc != 2)
        return 0;
    Triplet t;
    Solver s(string_to_int(argv[1]));
    t = s.solve();
    //s.print();
    //std::cout << std::endl;
    std::cout << "-> {" << t.first << " ," << t.second<< " ," << t.third << "};";
    return 0;
}
