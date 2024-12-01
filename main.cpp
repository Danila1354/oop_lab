#include "GameField.h"
#include "ShipManager.h"
#include "AbilityManager.h"
#include "Player.h"
#include "Bot.h"
#include "GameState.h"
#include "Game.h"



int main() {
    GameField player_field(10, 10, true);
    GameField bot_field(10, 10);
    ShipManager player_ship_manager = ShipManager{3, {1,2,3}};
    ShipManager bot_ship_manager = ShipManager{3, {1,2,3}};
    AbilityManager player_ability_manager = AbilityManager();
    Player player = Player(player_field, player_ship_manager, player_ability_manager);
    Bot bot = Bot(bot_field, bot_ship_manager);
    GameState game_state = GameState(player, bot);
    Game game = Game(game_state);
    game.begin();
    return 0;
}
