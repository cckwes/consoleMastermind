#include <random>
#include <algorithm>
#include <cstring>
#include <iostream>

#include "board.h"

Board::Board(size_t codeLength, bool colorDuplicate) :
    m_duplicate(colorDuplicate), m_codeLength(codeLength),
    m_remaining(10), m_pegsColor("wbrnlyoc")
{
}

Board::~Board()
{
}

bool Board::isCodeValid(const std::string &code)
{
    //check length
    if (code.length() != m_codeLength)
        return false;

    //check for invalid color code
    auto it = std::find_if(code.cbegin(), code.cend(),
                           [this](char c) {
        return (m_pegsColor.find(tolower(c)) == std::string::npos);
    });

    return it == code.cend();
}

bool Board::getResult(const std::string &code,
                      std::string &hint)
{
    if (m_remaining == 0)
    {
        hint = std::string(m_codeLength, '-');
        return false;
    }

    --m_remaining;
    //transform string to lower case
    std::string lowerCode;
    std::transform(code.begin(), code.end(),
                   std::back_inserter(lowerCode), tolower);

    //compare for exact match (WIN)
    if (lowerCode.compare(m_code) == 0)
    {
        hint = std::string(m_codeLength, 'O');
        return true;
    }

    //white represents correct color but incorrect position
    //black represents correct color and position
    int whiteCount = 0, blackCount = 0;

    std::string trueCodeCopy = m_code;

    //compare code by code
    size_t i = 0;
    for (const char &c : lowerCode)
    {
        if (c == trueCodeCopy[i])
        {
            ++blackCount;
            trueCodeCopy[i] = 0;
            ++i;
            continue;
        }
        else
        {
            //incorrect position but color is correct
            size_t pos = trueCodeCopy.find(c);

            if (pos == std::string::npos)
            {
                ++i;
                continue;
            }
            else if (pos < m_codeLength)
            {
                ++whiteCount;
                trueCodeCopy[pos] = 0;
                ++i;
                continue;
            }
        }
    }

    //pack the hint
    hint.append(std::string(blackCount, 'X'));
    hint.append(std::string(whiteCount, 'O'));
    hint.append(std::string(m_codeLength - whiteCount - blackCount, '-'));

    return false;
}

void Board::restartGame()
{
    generateCode();
    m_remaining = 10;
}

void Board::generateCode()
{
    m_code.clear();

    std::random_device rd;
    std::mt19937 g(rd());

    if (m_duplicate)
    {
        std::uniform_int_distribution<> dis(0, m_pegsColor.size() - 1);

        m_code.resize(m_codeLength);
        for (size_t i = 0; i < m_codeLength; ++i)
        {
            m_code[i] = m_pegsColor[dis(g)];
        }
    }
    else
    {
        std::vector<char> rand_container(m_pegsColor.begin(),
                                         m_pegsColor.end());

        std::shuffle(rand_container.begin(),
                     rand_container.end(), g);

        std::copy_n(rand_container.begin(), m_codeLength, std::back_inserter(m_code));
    }
}

void Board::printColorList()
{
    std::cout << "Color list:\n"
              << "W for white, B for Black\n"
              << "R for red, N for Green\n"
              << "L for blue, Y for Yellow\n"
              << "O for orange, C for brown\n";
}

void Board::printHintList()
{
    std::cout << "Hint: \n"
              << "'X' Correct color and position\n"
              << "'O' Correct color but not position\n";
}
