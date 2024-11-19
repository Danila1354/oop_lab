#ifndef BATTLESHIP_EXCEPTION_H
#define BATTLESHIP_EXCEPTION_H
#include <exception>
#include <string>

class BattleShipException : public std::exception {
protected:
    std::string message;

public:
    explicit BattleShipException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};


#endif // BATTLESHIP_EXCEPTION_H
