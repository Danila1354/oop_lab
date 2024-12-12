#include "Game.h"

Game::Game(GameState game_state) : game_state(game_state) {};


void Game::startNewGame(){
    game_state.getPlayer().randomPlaceShips();
    game_state.getBot().randomPlaceShips();
}

void Game::playerAttack(int x, int y){
    game_state.getPlayer().attack(game_state.getBot().getField(), x, y);
}

void Game::playerUseAbility(){
    game_state.getPlayer().useAbility(game_state.getBot());
}


std::pair<int,int> Game::botAttack() {
    int width = game_state.getPlayer().getField().getWidth();
    int height = game_state.getPlayer().getField().getHeight();
    std::srand(std::time(nullptr));
    int x = rand() % width;
    int y = rand() % height;
    game_state.getBot().attack(game_state.getPlayer().getField(), x, y);

    return std::make_pair(x, y);
}

void Game::saveGame() {
    {
        std::ofstream file("save.json");
        file << game_state;
    }
}

void Game::loadGame() {
    {
        std::ifstream file("save.json");

        if (!file.is_open()) {
            return startNewGame();
        }
        file >> game_state;
    }

}


void Game::resetGame() {
    game_state.resetGame();
}

void Game::resetRound() {
    game_state.resetRound();
}

GameState Game::getGameState() {
    return game_state;
}


