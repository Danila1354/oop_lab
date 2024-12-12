#ifndef OOP_LAB2_CONSOLERENDERER_H
#define OOP_LAB2_CONSOLERENDERER_H
#include <iostream>
#include "GameField.h"


class ConsoleRenderer{
private:
    void drawCell(Cell& cell);
public:
    void drawField(GameField& field);
    void printMessage(const std::string& message);
};


#endif //OOP_LAB2_CONSOLERENDERER_H
