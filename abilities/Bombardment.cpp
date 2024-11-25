#include "Bombardment.h"

Bombardment::Bombardment(ShipManager &ship_manager) : ship_manager(ship_manager) {}



AbilityResult Bombardment::apply() {
    if (ship_manager.isAllShipsDestroyed()) {
        return AbilityResult::AllShipsDestroyed;
    }

    std::vector<Ship*> not_destroyed_ships;
    for (auto &ship: ship_manager.getShips()) {
        if (!ship.isShipDestroyed()) {
            not_destroyed_ships.push_back(&ship);
        }
    }
    while (true) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> ship_dist(0, not_destroyed_ships.size()-1);
        auto random_ship = not_destroyed_ships[ship_dist(gen)];
        std::uniform_int_distribution<int> segment_dist(0, random_ship->getLength()-1);
        auto random_segment = segment_dist(gen);
        if (random_ship->getSegmentState(random_segment) != SegmentState::Destroyed){
            random_ship->takeDamage(random_segment);
            if (random_ship->isShipDestroyed()) {
                return AbilityResult::ShipDestroyed;
            }
            break;
        }
    }
    return AbilityResult::Success;
}