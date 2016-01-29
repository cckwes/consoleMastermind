#include <iostream>

#include "game.h"

int main()
{
    Game g;
    std::string inputString;

    while (1)
    {
        g.welcome();
        std::getline(std::cin, inputString);
        std::transform(inputString.begin(), inputString.end(), inputString.begin(), tolower);

        if (inputString == "r")
            g.start();
        else if (inputString == "s")
            g.settings();
        else if (inputString == "q")
            break;
        else
            std::cout << "Invalid input\n\n";
    }

    exit(0);
    return 0;
}

