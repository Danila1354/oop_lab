#ifndef OOP_LAB2_TERMINALHANDLER_H
#define OOP_LAB2_TERMINALHANDLER_H
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include "json.hpp"
using json = nlohmann::json;
enum class Command{
    NewGame,
    Attack,
    UseAbility,
    SaveGame,
    LoadGame,
    Exit,
    None
};

class TerminalHandler {
private:
    std::unordered_map<char, Command> command_map;
    std::unordered_map<std::string, char> command_key_map;

    void setDefaultCommands();

    bool loadCommandsFromFile(std::string& filename);

    bool validateCommands(json &j);
public:

    TerminalHandler(std::string& filename);

    Command getCommand(char input);

    char getInput();

    void printMainMenu();

    void printGameMenu();

    std::pair<int, int> getAttackCoordinates();
};


#endif //OOP_LAB2_TERMINALHANDLER_H
