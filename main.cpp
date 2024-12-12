#include "GameField.h"
#include "ShipManager.h"
#include "AbilityManager.h"
#include "Player.h"
#include "Bot.h"
#include "GameState.h"
#include "Game.h"
#include "TerminalHandler.h"
#include "ConsoleRenderer.h"
#include "GameDisplay.h"
#include "GameController.h"


int main() {
    GameField player_field(10, 10, true);
    GameField bot_field(10, 10);
    ShipManager player_ship_manager = ShipManager{4, {4,3,2,1}};
    ShipManager bot_ship_manager = ShipManager{4, {4,3,2,1}};
    AbilityManager player_ability_manager = AbilityManager();
    Player player = Player(player_field, player_ship_manager, player_ability_manager);
    Bot bot = Bot(bot_field, bot_ship_manager);
    GameState game_state = GameState(player, bot);
    Game game = Game(game_state);
    std::string commands_filename = "commands.json";
    TerminalHandler handler = TerminalHandler(commands_filename);
    ConsoleRenderer renderer = ConsoleRenderer();
    GameDisplay display = GameDisplay(renderer);
    GameController controller = GameController(game,handler, display);
    controller.start();
    return 0;
}
