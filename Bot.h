#ifndef OOP_LAB2_BOT_H
#define OOP_LAB2_BOT_H


class Bot : public Character {
public:
    Bot(GameField &field, ShipManager &ship_manager) : Character(field, ship_manager) {};
};


#endif //OOP_LAB2_BOT_H
