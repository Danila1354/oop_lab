#ifndef OOP_LAB2_GAME_H
#define OOP_LAB2_GAME_H

#include <iostream>
#include "GameState.h"


class Game {
private:
    GameState game_state;


public:
    Game(GameState game_state);

    void saveGame();

    void loadGame();

    std::pair<int,int> botAttack();

    void playerAttack(int x, int y);

    void playerUseAbility();

    void startNewGame();


    void resetGame();

    void resetRound();

    GameState getGameState();

};


#endif //OOP_LAB2_GAME_H
