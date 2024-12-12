#ifndef OOP_LAB2_GAMECONTROLLER_H
#define OOP_LAB2_GAMECONTROLLER_H
#include "Game.h"
#include "TerminalHandler.h"


template <typename InputHandler, typename Display>
class GameController {
private:
    Game &game;
    InputHandler &handler;
    Display& display;
public:
    GameController(Game &g, InputHandler &handler,Display& display) : game(g), handler(handler), display(display){}
    void start() {
        handler.printMainMenu();
        char command = handler.getInput();
        if (handler.getCommand(command) == Command::NewGame) {
            game.startNewGame();
            return startLoop();
        } else if (handler.getCommand(command) == Command::LoadGame) {
            game.loadGame();
            return startLoop();
        } else if (handler.getCommand(command) == Command::Exit) {
            exit(0);
        } else {
            display.printMessage("Error: Invalid command");
            return start();
        }
    }
    void startLoop(){
        display.printMessage("Round " + std::to_string(game.getGameState().getRound()) + " - Start");
        while(true){
            display.printMessage("Enemy field:");
            display.printField(game.getGameState().getBot().getField());
            playerMove();
            auto [x,y] = game.botAttack();
            display.printMessage("Bot attacked at " + std::to_string(x) + " " + std::to_string(y)+ " Your field:");
            display.printField(game.getGameState().getPlayer().getField());
            if (game.getGameState().isPlayerWin() || game.getGameState().isBotWin()) {
                break;
            }
        }
        if (game.getGameState().isPlayerWin()){
            display.printMessage("You won! Starting next round");
            game.resetRound();
            return startLoop();
        }
        else{
            display.printMessage("Starting a new game");
            game.resetGame();
            return startLoop();
        }
    }
    void playerMove() {
        handler.printGameMenu();
        char command = handler.getInput();
        if (handler.getCommand(command) == Command::Attack) {
            auto [x, y] = handler.getAttackCoordinates();
            game.playerAttack(x, y);
        } else if (handler.getCommand(command) == Command::UseAbility) {
            game.playerUseAbility();
            auto [x, y] = handler.getAttackCoordinates();
            game.playerAttack(x, y);
        } else if (handler.getCommand(command) == Command::SaveGame) {
            game.saveGame();
            display.printMessage("Game saved");
            return playerMove();
        } else if (handler.getCommand(command) == Command::LoadGame) {
            game.loadGame();
            return startLoop();
        } else if (handler.getCommand(command) == Command::Exit) {
            exit(0);
        } else {
            display.printMessage("Error: Invalid command");
            return playerMove();
        }
    }
};


#endif //OOP_LAB2_GAMECONTROLLER_H
