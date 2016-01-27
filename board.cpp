#include <random>
#include <algorithm>
#include "board.h"

Board::Board(int codeLength, bool colorDuplicate) :
    m_duplicate(colorDuplicate), m_codeLength(codeLength),
    m_pegsColor("wbrnlyoc")
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
    auto it = code.cbegin();

    while (it != code.cend())
    {
        auto found = m_pegsColor.find(*it);
        if (found == std::string::npos)
            return false;
        ++it;
    }

    return true;
}

void Board::generateCode()
{
    m_code.resize(m_codeLength);

    std::random_device rd;
    std::mt19937 g(rd());

    if (m_duplicate)
    {
        std::uniform_int_distribution<> dis(0, m_pegsColor.size() - 1);

        for (int i = 0; i < m_codeLength; ++i)
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

        for (int i = 0; i < m_codeLength; ++i)
        {
            m_code[i] = rand_container[i];
        }
    }
}
