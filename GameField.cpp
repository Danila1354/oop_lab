#include "GameField.h"

GameField::GameField(int width, int height) {
    if (!checkWidthAndHeight(width, height)) {
        std::cerr << "Width and height of the field must be positive" << '\n';
        width = 0;
        height = 0;
    }
    this->width = width;
    this->height = height;
    number_of_deployed_ships = 0;
    field.resize(height, std::vector<Cell>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            field[i][j] = Cell();
        }
    }
}

GameField::GameField(const GameField &other)
        : width(other.width), height(other.height), number_of_deployed_ships(other.number_of_deployed_ships) {
    field.resize(height);
    for (int i = 0; i < height; ++i) {
        field[i].resize(width);
        for (int j = 0; j < width; ++j) {
            field[i][j] = other.field[i][j];
        }
    }
}

GameField &GameField::operator=(const GameField &other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        number_of_deployed_ships = other.number_of_deployed_ships;
        field.resize(height);
        for (int i = 0; i < height; ++i) {
            field[i].resize(width);
            for (int j = 0; j < width; ++j) {
                field[i][j] = other.field[i][j];
            }
        }
    }
    return *this;
}

GameField::GameField(GameField &&other)
        : width(other.width), height(other.height), number_of_deployed_ships(other.number_of_deployed_ships) {
    field = std::move(other.field);
    other.width = 0;
    other.height = 0;
    other.number_of_deployed_ships = 0;
}

GameField &GameField::operator=(GameField &&other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        number_of_deployed_ships = other.number_of_deployed_ships;
        field = std::move(other.field);
        other.width = 0;
        other.height = 0;
        other.number_of_deployed_ships = 0;
    }
    return *this;
}


bool GameField::attackCell(int x, int y) {
    if (!checkCoords(x, y)) {
        throw OutOfBoundsAttackException();
    }
    if (!field[y][x].isOpen())
        field[y][x].open();
    if (field[y][x].getStatus() == Status::Occupied) {
        auto pointer_to_ship = field[y][x].getPointerToShip();
        auto index = field[y][x].getIndexOfSegment();
        pointer_to_ship->takeDamage(index);
        return pointer_to_ship->isShipDestroyed();
    }
    return false;
}

void GameField::show() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            field[i][j].display();
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

bool GameField::checkCollide(int x, int y) {
    int row_above = y-1;
    int row_below = y+1;
    int left_col = x-1;
    int right_col = x+1;
    for (int i = row_above;i<row_below+1;i++){
        for (int j = left_col;j<right_col+1;j++){
            if ((j == x && i == y) || (j<0 || i<0 || i>=height || j>=width))
                continue;
            else{
                if (field[i][j].getStatus() == Status::Occupied)
                    return false;
            }
        }
    }

    return true;

}

void GameField::setShipCoords(Ship &ship, int x, int y, int ship_length) {
    for (int i = 0; i < ship_length; i++) {
        if (ship.isVertical()) {
            field[y + i][x].setStatus(Status::Occupied);
            field[y + i][x].setPointerToShip(&ship);
            field[y + i][x].setIndexOfSegment(i);
        } else {
            field[y][x + i].setStatus(Status::Occupied);
            field[y][x + i].setPointerToShip(&ship);
            field[y][x + i].setIndexOfSegment(i);
        }
    }

}

void GameField::placeShip(Ship &ship, int x, int y, bool is_vertical) {
    auto ship_length = ship.getLength();
    int x_coord, y_coord;
    for (int i = 0; i < ship_length; i++) {
        if (is_vertical) {
            x_coord = x;
            y_coord = y + i;
        } else {
            x_coord = x + i;
            y_coord = y;
        }
        if (!checkCoords(x_coord,y_coord) || !checkCollide(x_coord, y_coord)) {
            throw ShipPlacementException();
        }
    }
    ship.setIsVertical(is_vertical);
    setShipCoords(ship, x, y, ship_length);
}

Cell& GameField::getCell(int x, int y){
    return field[y][x];
}

int GameField::getWidth() {
    return width;
}

int GameField::getHeight() {
    return height;
}

bool GameField::checkWidthAndHeight(int width, int height) {
    if (width < 0 || height < 0)
        return false;
    return true;
}

bool GameField::checkCoords(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return false;
    return true;
}
