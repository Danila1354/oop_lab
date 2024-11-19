#include "GameField.h"
#include "ShipManager.h"
#include "AbilityManager.h"

int main() {
    GameField field{10, 10};
    auto ship_manager = ShipManager(3, {3, 1, 2});
    int ships_coords[3][2] = {{5, 4},
                              {1, 4},
                              {9, 1}};
    auto &ships = ship_manager.getShips();
    bool positions[] = {false, false, true};
    for (int i = 0; i < 3; i++) {
        try{
            field.placeShip(ships[i], ships_coords[i][0], ships_coords[i][1], positions[i]);
        }
        catch (ShipPlacementException& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    field.show();

//    try{
//        field.attackCell(5,4);
//    }
//    catch (OutOfBoundsAttackException& e){
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//    auto ability_manager = AbilityManager();
//    try{
//        ability_manager.useAbility(field);
//    }
//    catch (NoAbilitiesException& e){
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//    field.show();
    return 0;
}
