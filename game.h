#ifndef GAME_H
#define GAME_H

class Board;

class Game
{
public:
    Game();
    ~Game();

    void welcome();
    bool start();
    void settings();

private:
    Board *b;
};

#endif
