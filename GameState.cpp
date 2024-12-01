#include "GameState.h"

GameState::GameState(Player player, Bot bot, int round) : player(player), bot(bot), round(round) {};


bool GameState::isPlayerWin() {
    return bot.getShipManager().isAllShipsDestroyed();
}

bool GameState::isBotWin() {
    return player.getShipManager().isAllShipsDestroyed();
}

void GameState::resetPlayer() {
    player.getField() = GameField(10, 10, true);
    player.getShipManager() = ShipManager(3, {1,2,3});
    player.getAbilityManager() = AbilityManager();
}

void GameState::resetBot() {
    bot.getField() = GameField(10, 10);
    bot.getShipManager() = ShipManager(3, {1,2,3});
}

void GameState::resetGame() {
    round = 0;
    resetPlayer();
    resetBot();
}

void GameState::resetRound() {
    round++;
    resetBot();
}

std::ostream &operator<<(std::ostream &out, GameState &game_state) {
    std::vector<FileDataWrite> files = {
            {"player_field.txt", [&game_state](std::ofstream& file) { file << game_state.player.getField(); }},
            {"player_ship_manager.txt", [&game_state](std::ofstream& file) { file << game_state.player.getShipManager(); }},
            {"player_ability_manager.txt", [&game_state](std::ofstream& file) { file << game_state.player.getAbilityManager(); }},
            {"bot_field.txt", [&game_state](std::ofstream& file) { file << game_state.bot.getField(); }},
            {"bot_ship_manager.txt", [&game_state](std::ofstream& file) { file << game_state.bot.getShipManager(); }}
    };

    out << game_state.round << '\n';
    for (const auto& fileData : files) {
        std::ofstream file(fileData.filename);
        if (file.is_open()) {
            fileData.writeFunc(file);
        }
    }

    return out;
}

std::istream &operator>>(std::istream &in, GameState &game_state) {


    std::vector<FileDataRead> files = {
            {"player_ship_manager.txt", [&game_state](std::ifstream& file) { file >> game_state.player.getShipManager(); }},
            {"player_field.txt", [&game_state](std::ifstream& file) { game_state.player.getField().loadFieldAndShips(file, game_state.player.getField(), game_state.player.getShipManager()); }},
            {"player_ability_manager.txt", [&game_state](std::ifstream& file) { file >> game_state.player.getAbilityManager(); }},
            {"bot_ship_manager.txt", [&game_state](std::ifstream& file) { file >> game_state.bot.getShipManager(); }},
            {"bot_field.txt", [&game_state](std::ifstream& file) { game_state.bot.getField().loadFieldAndShips(file, game_state.bot.getField(), game_state.bot.getShipManager()); }}
    };
    in >> game_state.round;
    for (const auto& fileData : files) {
        std::ifstream file(fileData.filename);
        if (file.is_open()) {
            fileData.readFunc(file);
        }
    }

    return in;
}

int GameState::getRound() { return round; }

Player &GameState::getPlayer() { return player; }

Bot &GameState::getBot() { return bot; }
