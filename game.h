#ifndef GAME_H
#define GAME_H

class Board;

class Game
{
public:
    Game();
    ~Game();

    void start();

private:
    void settings();
    void welcome();
    int startGame();

    Board *b;
};

#endif
