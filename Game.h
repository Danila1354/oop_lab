#ifndef OOP_LAB2_GAME_H
#define OOP_LAB2_GAME_H
#include <iostream>
#include "GameState.h"
#include "ConsoleIO.h"
class Game {
private:
    GameState game_state;
    ConsoleIO console_io;

    void start(bool is_new_game = true);
    void playerMove();
    void botMove();
    void saveGame();
    void loadGame();
public:
    Game(GameState game_state);
    void begin();


};



#endif //OOP_LAB2_GAME_H
