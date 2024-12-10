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
    json j;
    j["round"] = game_state.round;
    game_state.bot.getField().to_json(j,false);
    game_state.player.getAbilityManager().to_json(j);
    game_state.player.getField().to_json(j,true);
    out << j;
    return out;
}

std::istream &operator>>(std::istream &in, GameState &game_state) {
    json j;
    in >> j;
    game_state.round = j["round"];
    game_state.bot.getField().from_json(j,game_state.bot.getShipManager(),false);
    game_state.player.getAbilityManager().from_json(j);
    game_state.player.getField().from_json(j, game_state.player.getShipManager(),true);
    return in;
}

int GameState::getRound() { return round; }

Player &GameState::getPlayer() { return player; }

Bot &GameState::getBot() { return bot; }
