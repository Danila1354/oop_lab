#ifndef OOP_LAB2_GAMESTATE_H
#define OOP_LAB2_GAMESTATE_H
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Bot.h"
#include "GameField.h"
#include "AbilityManager.h"

struct FileDataRead {
    const char* filename;
    std::function<void(std::ifstream&)> readFunc;
};

struct FileDataWrite {
    const char* filename;
    std::function<void(std::ofstream&)> writeFunc;
};


class GameState {
private:
    int round;
    Player player;
    Bot bot;
    void resetPlayer();

    void resetBot();



public:
    GameState(Player player, Bot bot,int round = 0);

    friend std::ostream &operator<<(std::ostream &out, GameState &game_state);

    friend std::istream &operator>>(std::istream &in, GameState &game_state);

    bool isPlayerWin();

    bool isBotWin();

    int getRound();

    Player& getPlayer();

    Bot& getBot();

    void resetGame();

    void resetRound();




};



#endif //OOP_LAB2_GAMESTATE_H
