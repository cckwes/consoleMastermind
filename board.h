#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

enum PegsColor {
    White = 'w',
    Black = 'b',
    Red = 'r',
    Green = 'n',
    Blue = 'l',
    Yellow = 'y',
    Orange = 'o',
    Brown = 'c'
};

class Board
{
public:
    Board(int codeLength = 4, bool colorDuplicate = false);
    ~Board();

    inline void setCodeLength(int codeLength) {
        if (codeLength >= 4 && codeLength <= 8)
            m_codeLength = codeLength;
        else
            m_codeLength = 4;
    }
    inline void setDuplicate(bool enabled) {m_duplicate = enabled;}

    //check code for valid length and character
    bool isCodeValid(const std::string &code);

    //generate code for new game
    void generateCode();

    //remove during production
    inline std::string getCode() {return m_code;}


private:
    bool m_duplicate;
    int m_codeLength;
    std::string m_pegsColor;
    std::string m_code;
};

#endif // BOARD_H
