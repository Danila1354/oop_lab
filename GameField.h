#ifndef OOP_LAB1_GAMEFIELD_H
#define OOP_LAB1_GAMEFIELD_H

#include <iostream>
#include "Cell.h"
#include "ShipManager.h"
#include "OutOfBoundsAttackException.h"
#include "ShipPlacementException.h"
#include <sstream>



class GameField {
private:
    std::vector<std::vector<Cell>> field;
    int width;
    int height;
    int number_of_deployed_ships;

    bool checkCollide(int x, int y);

    bool checkCoords(int x, int y);

    bool checkWidthAndHeight(int width, int height);

    void setShipCoords(Ship &ship, int x, int y, int ship_length);

public:
    GameField(int width, int height, bool is_open_cells = false);

    GameField(const GameField &other);

    GameField &operator=(const GameField &other);

    GameField(GameField &&other);

    GameField &operator=(GameField &&other);

    bool attackCell(int x, int y, bool is_double_attack = false);

    void show();

    void placeShip(Ship &ship, int x, int y, bool is_vertical);

    Cell& getCell(int x, int y);

    int getWidth();

    int getHeight();

    friend std::ostream &operator<<(std::ostream &out, GameField &field);

    friend std::istream &operator>>(std::istream &in, GameField &field);

    void loadFieldAndShips(std::istream &in, GameField &field, ShipManager &ship_manager);





};


#endif //OOP_LAB1_GAMEFIELD_H
