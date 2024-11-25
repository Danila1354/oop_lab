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
    CoordHolder coord_holder;
    InfoHolder info_holder{field, ship_manager, coord_holder};

    auto ability_manager = AbilityManager();
    try{
        ability_manager.useAbility(info_holder);
    }
    catch (NoAbilitiesException& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try{
        if (field.attackCell(5,4)){
            ability_manager.addRandomAbility();
        }
    }
    catch (OutOfBoundsAttackException& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    field.show();
    return 0;
}
