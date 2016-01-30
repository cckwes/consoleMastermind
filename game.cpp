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
              << "Enter 'R' to start game\n"
              << "Enter 'S' for game settings\n"
              << "Enter 'Q' to quit the game\n";
}

void Game::start()
{
    std::string inputString;

    while (1)
    {
        welcome();
        std::getline(std::cin, inputString);
        std::transform(inputString.begin(), inputString.end(),
                       inputString.begin(), tolower);

        if (inputString == "r")
        {
            int ret = startGame();
            if (ret == 1)
                break;
            else
                continue;
        }
        else if (inputString == "s")
            settings();
        else if (inputString == "q")
            break;
        else
            std::cout << "Invalid input\n\n";
    }
}

int Game::startGame()
{
    b->printColorList();
    b->printHintList();
    std::cout << "Command: \n"
              << "'Q' to quit, 'R' to start a new game\n";

    b->restartGame();

    while (b->getRemaining() != 0)
    {
        std::string inputString;
        std::cout << "[" << b->getRemaining() << "] Code:\t";
        std::getline(std::cin, inputString);

        if (inputString == "Q" || inputString == "q")
            return 1;
        else if (inputString == "R" || inputString == "r")
            return 2;

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
            return 0;
        }
        else
        {
            //display hint here
            std::cout << "Hint:\t" << hint << "\n";
        }
    }

    std::cout << "Run out of moves!";
    std::cout << "Correct code:\t" << b->getCode() << "\n";
    return 0;
}

void Game::settings()
{
    std::string settingsString;

    //prompt for code duplication settings
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
            {
                b->setDuplicate(true);
                break;
            }
            else if (settingsString == "n")
            {
                b->setDuplicate(false);
                break;
            }
            else
            {
                std::cout << "Invalid input\n";
                continue;
            }
        }
    }

    //prompt for code length settings
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
