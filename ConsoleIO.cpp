#include "ConsoleIO.h"

int ConsoleIO::getMenuCommand() {
    std::cout << "Do you want to start a new game or load the previous one?\n";
    std::cout << "[1] - New game\n";
    std::cout << "[2] - Load game\n";
    std::cout << "[3] - Exit\n";
    std::cout << "Choose the command: ";
    int command;
    std::cin >> command;
    return command;
}

int ConsoleIO::getPlayerCommand() {
    std::cout << "Player's move\n";
    std::cout << "[1] - Attack\n";
    std::cout << "[2] - Use ability\n";
    std::cout << "[3] - Save game\n";
    std::cout << "[4] - Load game\n";
    std::cout << "[5] - Exit\n";
    std::cout << "Choose the command: ";
    int command;
    std::cin >> command;
    return command;
}

std::pair<int, int> ConsoleIO::getAttackCoordinates() {
    int x, y;
    std::cout << "Enter attack coordinates (x y): ";
    std::cin >> x >> y;
    return {x, y};
}

void ConsoleIO::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
}
