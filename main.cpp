#include <iostream>

#include "board.h"

int main()
{
    Board b;
    b.setDuplicate(true);
    b.generateCode();
    std::cout << b.getCode() << "\n";

    exit(0);
    return 0;
}

