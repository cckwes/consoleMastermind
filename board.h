#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

/*
    White = 'w',
    Black = 'b',
    Red = 'r',
    Green = 'n',
    Blue = 'l',
    Yellow = 'y',
    Orange = 'o',
    Brown = 'c'
*/

class Board
{
public:
    Board(size_t codeLength = 4, bool colorDuplicate = false);
    ~Board();

    inline void setCodeLength(size_t codeLength) {
        if (codeLength >= 4 && codeLength <= 8)
            m_codeLength = codeLength;
        else
            m_codeLength = 4;
    }
    inline void setDuplicate(bool enabled) {m_duplicate = enabled;}
    inline size_t getRemaining() {return m_remaining;}
    inline bool getDuplicate() {return m_duplicate;}
    inline size_t getCodeLength() {return m_codeLength;}

    //check code for valid length and character
    bool isCodeValid(const std::string &code);

    //submit code and get result
    bool getResult(const std::string &code,
                   std::string &hint);

    //restart game
    void restartGame();

    //remove during production
    inline std::string getCode() {return m_code;}


private:
    //generate code for new game
    void generateCode();

    bool m_duplicate;               //allow/disallow duplication
    size_t m_codeLength;               //code length [4,8]
    size_t m_remaining;                //number of trial remaining
    std::string m_pegsColor;        //store the colors available
    std::string m_code;             //store the code generated
};

#endif // BOARD_H
