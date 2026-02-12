#include "UserInput.hpp"
#include <algorithm>
#include <iostream>

UserInput::UserInput(Circuit & circuit) : _circuit(circuit) {
    _map["exit"] = [this](std::string, nts::Tristate) {_Exit();};
    _map["display"] = [this](std::string, nts::Tristate)  {_Display();};
    _map["simulate"] = [this](std::string, nts::Tristate)  {_Simulate();};
    _map["loop"] = [this](std::string, nts::Tristate)  {_Loop();};
    _map["other"] = [this] (std::string name, nts::Tristate val)  {_UpdateVal(name, val);};
};

nts::Tristate getState(std::string val) {
    if (val == "0")
        return nts::False;
    if (val == "1")
        return nts::True;
    if (val == "U")
        return nts::Undefined;
    return nts::Undefined;
}

void UserInput::updateVal(std::string line) {
    size_t pos = line.find('=');
    if (pos == std::string::npos) {
    return;
    }
    std::string name = line.substr(0, pos);
    _circuit.updateInput(name, getState(line.substr(pos + 1)));
}

void UserInput::_Display() {
    std::cout <<"tick: ";
    /// need a get tick function
    std::cout << "input(s):" << std::endl;
    _circuit.printInputs();
    std::cout << "output(s):" << std::endl;
    _circuit.printoutputs();
};
void UserInput::_Simulate(){};

void UserInput::_Loop(){
    while (1)
    {
        _Simulate();
        _Display();
    }
};

void UserInput::runInputs(){
    std::cout << "> ";
    std::cin >> _input;
    while (_input != "exit") {
        if (_map.find(_input) != _map.end()) {
            _map[_input];
        } else {
            _map["other"];
        }
        std::cout << "> ";
        std::cin >> _input;
    }
};

UserInput::~UserInput(){};