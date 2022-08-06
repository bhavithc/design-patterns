#include <iostream>
#include "Creational.h"

int main()
{
    MazeGame mg;
    auto pMaze = mg.createMaze();

    auto pRoom1 = pMaze->roomNr(1);
    auto pRoom2 = pMaze->roomNr(2);

    std::cout << pRoom1->roomNr() << ", " << pRoom2->roomNr() << "\n";

    return 0;
}