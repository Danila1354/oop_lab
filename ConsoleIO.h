#ifndef OOP_LAB2_CONSOLEIO_H
#define OOP_LAB2_CONSOLEIO_H
#include <iostream>

class ConsoleIO {
public:
    int getMenuCommand();
    int getPlayerCommand();
    std::pair<int, int> getAttackCoordinates();
    void displayMessage(const std::string& message);
};


#endif //OOP_LAB2_CONSOLEIO_H
