#include "TerminalHandler.h"

TerminalHandler::TerminalHandler(std::string& filename){
    if(!loadCommandsFromFile(filename)){
        setDefaultCommands();
    }
}
void TerminalHandler::setDefaultCommands(){
    command_key_map["New game"] = 'n';
    command_key_map["Attack"] = 'a';
    command_key_map["Use ability"] = 'e';
    command_key_map["Save game"] = 's';
    command_key_map["Load game"] = 'l';
    command_key_map["Exit"] = 'q';
    command_map[command_key_map["New game"]] = Command::NewGame;
    command_map[command_key_map["Attack"]] = Command::Attack;
    command_map[command_key_map["Use ability"]] = Command::UseAbility;
    command_map[command_key_map["Save game"]] = Command::SaveGame;
    command_map[command_key_map["Load game"]] =Command::LoadGame;
    command_map[command_key_map["Exit"]] = Command::Exit;
}

bool TerminalHandler::loadCommandsFromFile(std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    json j;
    file >> j;
    if (!validateCommands(j)){
        return false;
    }
    for (auto& [key, value] : j.items()) {
        char command_char = value.get<std::string>()[0];
        if (key == "Attack") {
            command_key_map["Attack"] = command_char;
            command_map[command_char] = Command::Attack;;
        } else if (key == "Use ability") {
            command_key_map["Use ability"] = command_char;
            command_map[command_char] = Command::UseAbility;;
        } else if (key == "Save game") {
            command_key_map["Save game"] = command_char;
            command_map[command_char] = Command::SaveGame;;
        } else if (key == "Load game") {
            command_key_map["Load game"] = command_char;
            command_map[command_char] = Command::LoadGame;;
        } else if (key == "Exit") {
            command_key_map["Exit"] = command_char;
            command_map[command_char] = Command::Exit;;
        }
        else if(key == "New game"){
            command_key_map["New game"] = command_char;
            command_map[command_char] = Command::NewGame;;
        }
    }
    return true;
}
bool TerminalHandler::validateCommands(json &j) {
    std::vector<std::string> required_commands = {"Attack", "Use ability", "Save game", "Load game", "Exit", "New game"};
    for (const auto& command : required_commands) {
        if (j.find(command) == j.end()) {
            return false;
        }
    }
    std::unordered_set<char> used_keys;
    for (const auto& [command, key_json] : j.items()) {
        std::string key = key_json.get<std::string>();
        if (key.empty()) {
            return false;
        }
        char key_char = key[0];
        if (used_keys.find(key_char) != used_keys.end()) {
            return false;
        }
        used_keys.insert(key_char);
    }
    return true;
}
Command TerminalHandler::getCommand(char input) {
    if (command_map.find(input) == command_map.end()) {
        return Command::None;
    }
    return command_map[input];
}
char TerminalHandler::getInput() {
    char command;
    std::cin >> command;
    return command;
}

void TerminalHandler::printMainMenu(){
    std::cout << "Do you want to start a new game or load the previous one?\n";
    std::cout << "[" << command_key_map["New game"] << "] - New game\n";
    std::cout << "[" << command_key_map["Load game"] << "] - Load game\n";
    std::cout << "[" << command_key_map["Exit"] << "] - Exit\n";
    std::cout << "Choose the command: ";
}

void TerminalHandler::printGameMenu(){
    std::cout << "Player's move\n";
    std::cout << "[" << command_key_map["Attack"] << "] - Attack\n";
    std::cout << "[" << command_key_map["Use ability"] << "] - Use ability\n";
    std::cout << "[" << command_key_map["Save game"] << "] - Save game\n";
    std::cout << "[" << command_key_map["Load game"] << "] - Load game\n";
    std::cout << "[" << command_key_map["Exit"] << "] - Exit\n";
    std::cout << "Choose the command: ";
}

std::pair<int, int> TerminalHandler::getAttackCoordinates() {
    std::cout << "Enter the coordinates of the cell you want to attack\n";
    int x, y;
    std::cout << "Enter x and y: ";
    std::cin >> x >> y;
    return {x, y};
}

