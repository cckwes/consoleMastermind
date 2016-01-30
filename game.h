#ifndef GAME_H
#define GAME_H

class Board;

class Game
{
public:
    Game();
    ~Game();

    void welcome();
    int start();
    void settings();

private:
    Board *b;
};

#endif
