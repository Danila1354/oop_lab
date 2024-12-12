#include "GameField.h"

GameField::GameField(int width, int height, bool is_open_cells) {
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
            field[i][j] = Cell(is_open_cells);
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


bool GameField::attackCell(int x, int y, bool is_double_attack) {
    if (!checkCoords(x, y)) {
        throw OutOfBoundsAttackException();
    }

    if (!field[y][x].isOpen())
        field[y][x].open();
    if (field[y][x].getStatus() == Status::Occupied) {
        auto pointer_to_ship = field[y][x].getPointerToShip();
        if (pointer_to_ship->isShipDestroyed()){
            return false;
        }
        auto index = field[y][x].getIndexOfSegment();
        pointer_to_ship->takeDamage(index);
        if (is_double_attack)
            pointer_to_ship->takeDamage(index);
        return pointer_to_ship->isShipDestroyed();
    }
    return false;
}


bool GameField::checkCollide(int x, int y) {
    int row_above = y - 1;
    int row_below = y + 1;
    int left_col = x - 1;
    int right_col = x + 1;
    for (int i = row_above; i < row_below + 1; i++) {
        for (int j = left_col; j < right_col + 1; j++) {
            if ((j == x && i == y) || (j < 0 || i < 0 || i >= height || j >= width))
                continue;
            else {
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
        if (!checkCoords(x_coord, y_coord) || !checkCollide(x_coord, y_coord)) {
            throw ShipPlacementException();
        }
    }
    ship.setIsVertical(is_vertical);
    setShipCoords(ship, x, y, ship_length);
}

Cell &GameField::getCell(int x, int y) {
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

void GameField::to_json(json &j,bool is_player_field){
    j["height"] = this->getHeight();
    j["width"] = this->getWidth();
    json field_json = json::array();

    std::vector<int> ship_sizes;
    std::vector<std::pair<int, int>> ship_coords;
    std::vector<bool> is_vertical;

    for (int i = 0; i < this->height; i++) {
        json row = json::array();
        for (int j = 0; j < this->width; j++) {
            json cell_json;

            char is_open = field[i][j].isOpen() ? 'o' : 'c';
            cell_json["is_open"] = (is_open == 'o');

            if (field[i][j].getStatus() == Status::Empty) {
                cell_json["status"] = 0;
            } else {
                auto segment_index = field[i][j].getIndexOfSegment();
                auto segment_state = field[i][j].getPointerToShip()->getSegmentState(segment_index);

                if (segment_state == SegmentState::FULL) {
                    cell_json["status"] = 3;
                } else if (segment_state == SegmentState::Damaged) {
                    cell_json["status"] = 2;
                } else {
                    cell_json["status"] = 1;
                }

                if (segment_index == 0) {
                    ship_sizes.push_back(field[i][j].getPointerToShip()->getLength());
                    ship_coords.emplace_back(j, i);
                    is_vertical.push_back(field[i][j].getPointerToShip()->isVertical());
                }
            }

            row.push_back(cell_json);
        }
        field_json.push_back(row);
    }
    if (is_player_field)
        j["player_field"] = field_json;
    else
        j["bot_field"] = field_json;
    json ships_json = json::array();
    for (size_t i = 0; i < ship_sizes.size(); i++) {
        ships_json.push_back({
                                     {"size", ship_sizes[i]},
                                     {"x", ship_coords[i].first},
                                     {"y", ship_coords[i].second},
                                     {"is_vertical", is_vertical[i]}
                             });
    }
    if (is_player_field)
        j["player_ships"] = ships_json;
    else
        j["bot_ships"] = ships_json;
}

void GameField::from_json(const json &j, ShipManager &ship_manager,bool is_player_field) {
    *this = GameField(j["width"], j["height"]);
    auto ships_json = j[is_player_field ? "player_ships" : "bot_ships"];
    std::vector<int> ship_sizes;
    std::vector<std::pair<int, int>> ship_coords;
    std::vector<bool> is_vertical;
    for (size_t i = 0; i < ships_json.size(); i++) {
        ship_sizes.push_back(ships_json[i]["size"]);
        ship_coords.emplace_back(ships_json[i]["x"], ships_json[i]["y"]);
        is_vertical.push_back(ships_json[i]["is_vertical"]);
    }
    ship_manager = ShipManager(ship_sizes.size(), ship_sizes);
    auto &ships = ship_manager.getShips();
    for (size_t i = 0; i < ship_sizes.size(); i++) {
        placeShip(ships[i], ship_coords[i].first, ship_coords[i].second, is_vertical[i]);
    }


    auto field_json = j[is_player_field ? "player_field" : "bot_field"];
    for (size_t i = 0; i < field_json.size(); i++) {
        auto row = field_json[i];
        for (size_t j = 0; j < row.size(); j++) {
            auto cell_json = row[j];
            if (cell_json["is_open"]) {
                field[i][j].open();
            }
            if (cell_json["status"] != 0) {
                auto segment_index = field[i][j].getIndexOfSegment();
                auto ship = field[i][j].getPointerToShip();
                if (cell_json["status"] == 3) {
                    ship->setSegmentState(segment_index, SegmentState::FULL);
                } else if (cell_json["status"] == 2) {
                    ship->setSegmentState(segment_index, SegmentState::Damaged);
                } else if (cell_json["status"] == 1) {
                    ship->setSegmentState(segment_index, SegmentState::Destroyed);
                }
            }
        }
    }
}


