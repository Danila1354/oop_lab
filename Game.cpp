#include "Game.h"

Game::Game(GameState game_state) : game_state(game_state), console_io(ConsoleIO()) {};

void Game::begin() {
    int command;
    command = console_io.getMenuCommand();
    switch (command) {
        case 1:
            return start();
        case 2:
            return loadGame();
        case 3:
            exit(0);
        default:
            std::cerr << "Error: Invalid command\n";
    }
}

void Game::start(bool is_new_game) {
    while (true) {
        console_io.displayMessage("Round " + std::to_string(game_state.getRound()) + " - Start");
        if (is_new_game) {
            game_state.getPlayer().PlaceShips();
            game_state.getBot().PlaceShips();
        }
        while (true) {
            console_io.displayMessage("Enemy field:");
            game_state.getBot().getField().show();
            playerMove();
            botMove();
            game_state.getPlayer().getField().show();

            if (game_state.isPlayerWin() || game_state.isBotWin()) {
                break;
            }
        }
        if (game_state.isPlayerWin()) {
            console_io.displayMessage("You won! Starting next round");
            game_state.resetRound();
        } else {
            console_io.displayMessage("Starting a new game");
            game_state.resetGame();
        }
    }
}

void Game::playerMove() {
    int command;
    command = console_io.getPlayerCommand();
    while (true) {
        if (command == 1) {
            auto [x, y] = console_io.getAttackCoordinates();
            game_state.getPlayer().attack(game_state.getBot().getField(), x, y);
            break;
        } else if (command == 2) {
            try {
                game_state.getPlayer().useAbility(game_state.getBot());
                command = 1;

            } catch (NoAbilitiesException &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (command == 3) {
            console_io.displayMessage("Game saved");
            return saveGame();
        } else if (command == 4) {
            return loadGame();
        } else if (command == 5) {
            exit(0);
        } else {
            std::cerr << "Error: Invalid command\n";
        }
    }
}

void Game::botMove() {
    int width = game_state.getPlayer().getField().getWidth();
    int height = game_state.getPlayer().getField().getHeight();
    std::srand(std::time(nullptr));
    int x = rand() % width;
    int y = rand() % height;
    game_state.getBot().attack(game_state.getPlayer().getField(), x, y);
    console_io.displayMessage("Bot attack " + std::to_string(x) + " " + std::to_string(y) + "\n" + "Your field:");
}

void Game::saveGame() {
    {
        std::ofstream file("save.txt");
        file << game_state;
    }
}

void Game::loadGame() {
    {
        std::ifstream file("save.txt");

        if (!file.is_open()) {
            return start();
        }
        file >> game_state;
    }
    return start(false);
}


