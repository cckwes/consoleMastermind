#include <iostream>
#include <string>
#include <algorithm>

#include "board.h"
#include "game.h"

Game::Game()
{
    b = new Board();
}

Game::~Game()
{
    delete b;
}

void Game::welcome()
{
    std::cout << "Welcome to console Mastermind\n"
              << "Enter \'R\' to start game\n"
              << "Enter \'S\' for game settings\n"
              << "Enter \'Q\' to quit the game\n";
}

bool Game::start()
{
    std::cout << "Color list:\n"
              << "W for white, B for Black\n"
              << "R for red, N for Green\n"
              << "L for blue, Y for Yellow\n"
              << "O for orange, C for brown\n"
              << "Hint: \n"
              << "'X' Correct color and position\n"
              << "'O' Correct color but not position\n";

    b->restartGame();

    while (b->getRemaining() != 0)
    {
        std::string inputString;
        std::cout << "[" << b->getRemaining() << "] Code:\t";
        std::getline(std::cin, inputString);

        while (!b->isCodeValid(inputString))
        {
            std::cout << "Invalid code, please try again.\n";
            std::cout << "[" << b->getRemaining() << "] Code:\t";
            std::getline(std::cin, inputString);
        }

        std::string hint;

        if (b->getResult(inputString, hint))
        {
            std::cout << "You won!\n";
            return true;
        }
        else
        {
            //display hint here
            std::cout << "Hint:\t" << hint << "\n";
        }
    }

    std::cout << "Run out of moves!";
    return false;
}

void Game::settings()
{
    std::string settingsString;

    while (1)
    {
        std::cout << "Allow duplicate code ";

        if (b->getDuplicate())
            std::cout << "(Y/n):\t";
        else
            std::cout << "(y/N):\t";

        std::getline(std::cin, settingsString);

        //empty, use default
        if (settingsString.empty())
            break;
        else if (settingsString.length() != 1)
        {
            std::cout << "Invalid input\n";
            continue;
        }
        else
        {
            std::transform(settingsString.begin(), settingsString.end(), settingsString.begin(), tolower);

            if (settingsString == "y")
                b->setDuplicate(true);
            else if (settingsString == "n")
                b->setDuplicate(false);
            else
            {
                std::cout << "Invalid input\n";
                continue;
            }
        }
    }

    while (1)
    {
        std::cout << "Code length (" << b->getCodeLength() << "):\t";
        std::getline(std::cin, settingsString);

        if (settingsString.empty())
            break;

        int length = std::stoi(settingsString);

        if (length >= 4 && length <= 8)
        {
            b->setCodeLength(length);
            break;
        }
        else
        {
            std::cout << "Invalid input, code length must be between 4 and 8\n";
            continue;
        }
    }
}
