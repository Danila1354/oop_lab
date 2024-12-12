#ifndef OOP_LAB2_GAMEDISPLAY_H
#define OOP_LAB2_GAMEDISPLAY_H
#include "GameField.h"
#include <iostream>

template <typename GameRenderer>
class GameDisplay {
private:
    GameRenderer renderer;

public:
    GameDisplay(GameRenderer& renderer) : renderer(renderer) {}

    void printField(GameField& field) {
        renderer.drawField(field);
    }

    void printMessage(const std::string& message) {
        renderer.printMessage(message);
    }


};


#endif //OOP_LAB2_GAMEDISPLAY_H
