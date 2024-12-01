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
        auto index = field[y][x].getIndexOfSegment();
        pointer_to_ship->takeDamage(index);
        if (is_double_attack)
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

std::ostream &operator<<(std::ostream &out, GameField &field) {
    out << "height=" << field.getHeight() << "\n";
    out << "width=" << field.getWidth() << "\n";
    std::vector<int> ship_sizes;
    std::vector<std::pair<int, int>> ship_coords;
    std::vector<bool> is_vertical;
    for (int i = 0; i < field.height; i++) {
        for (int j = 0; j < field.width; j++) {
            char is_open = field.field[i][j].isOpen() ? 'o' : 'c';
            if (field.field[i][j].getStatus() == Status::Empty) {
                out << "0" << is_open;
            } else {
                auto segment_index = field.field[i][j].getIndexOfSegment();
                auto segment_state = field.field[i][j].getPointerToShip()->getSegmentState(segment_index);
                if (segment_state == SegmentState::FULL) {
                    out << "3" << is_open;
                } else if (segment_state == SegmentState::Damaged) {
                    out << "2" << is_open;
                } else {
                    out << "1" << is_open;
                }
                if (segment_index == 0) {
                    ship_sizes.push_back(field.field[i][j].getPointerToShip()->getLength());
                    ship_coords.emplace_back(j, i);
                    is_vertical.push_back(field.field[i][j].getPointerToShip()->isVertical());
                }

            }
        }
        if (i != field.height - 1) {
            out << '\n';
        }
    }
    for (int i = 0; i < ship_sizes.size(); i++) {
        out << '\n' << ship_sizes[i] << " " << ship_coords[i].first << " " << ship_coords[i].second << " "
            << is_vertical[i];
    }
    return out;
}


void GameField::loadFieldAndShips(std::istream &in, GameField &field, ShipManager &ship_manager) {
    std::string line;
    std::getline(in, line);
    int height = 0, width = 0;
    std::sscanf(line.c_str(), "height=%d", &height);
    std::getline(in, line);
    std::sscanf(line.c_str(), "width=%d", &width);
    field = GameField(width, height);
    for (int i = 0; i < height; i++) {
        std::getline(in, line);
    }
    std::vector<int> ship_sizes;
    std::vector<std::pair<int, int>> ship_coords;
    std::vector<bool> is_vertical;

    while (std::getline(in, line)) {
        std::istringstream ss(line);
        int size, x, y, vertical;
        ss >> size >> x >> y >> vertical;
        ship_sizes.push_back(size);
        ship_coords.push_back({x, y});
        is_vertical.push_back(vertical);
    }
    ship_manager = ShipManager(ship_sizes.size(), ship_sizes);
    auto &ships = ship_manager.getShips();
    for (int i = 0; i < ship_sizes.size(); i++) {
        field.placeShip(ships[i], ship_coords[i].first, ship_coords[i].second, is_vertical[i]);
    }

    in.clear();
    in.seekg(0, std::ios::beg);
    std::getline(in, line);
    std::getline(in, line);

    for (int i = 0; i < height; ++i) {
        std::getline(in, line);
        int x = 0;
        for (int j = 0; j < width; ++j) {
            char status = line[x];
            char is_open = line[x + 1];
            x += 2;
            if (status != '0') {
                auto segment_index = field.field[i][j].getIndexOfSegment();
                auto ship = field.field[i][j].getPointerToShip();
                if (status == '3') {
                    ship->setSegmentState(segment_index, SegmentState::FULL);
                } else if (status == '2') {
                    ship->setSegmentState(segment_index, SegmentState::Damaged);
                } else if (status == '1') {
                    ship->setSegmentState(segment_index, SegmentState::Destroyed);
                }
            }
            if (is_open == 'o') {
                field.getCell(j, i).open();
            }
        }
    }

}
