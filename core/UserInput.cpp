#include "include/core/UserInput.hpp"
#include <algorithm>
#include <iostream>

UserInput::UserInput(Circuit &circuit) : _circuit(circuit) {
    _map["display"] = [this]()  {_Display();};
    _map["simulate"] = [this]()  {_Simulate();};
    _map["loop"] = [this]()  {_Loop();};
    _map["other"] = [] ()  {};
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
    // std::cout << "in update" << std::endl;
    size_t pos = line.find('=');
    if (pos == std::string::npos) {
    return;
    }
    nameVal nv;
    nv.name = line.substr(0, pos);
    nv.state = getState(line.substr(pos + 1));
    updateQueue.push(nv);
}

void UserInput::_Display() {
    std::cout <<"tick: ";
    std::cout << _circuit.getTick();
    std::cout << std::endl;
    std::cout << "input(s):" << std::endl;
    _circuit.printInputs();
    std::cout << "output(s):" << std::endl;
    _circuit.printoutputs();
};
void UserInput::_Simulate(){
    while (!updateQueue.empty()) {
        nameVal temp = updateQueue.front();
        updateQueue.pop();
        _circuit.updateInput(temp.name, temp.state);
    }
    _circuit.oneTick();
};

void UserInput::_Loop() {
    while (1) {
        _Simulate();
        _Display();
    }
}



void UserInput::runInputs(){
    std::cout << "> ";
    std::cin >> _input;
    while (_input != "exit") {
        if (_map.find(_input) != _map.end()) {

            _map[_input]();
        } else {
            updateVal(_input);
        }
        std::cout << "> ";
        std::cin >> _input;
    }
};

UserInput::~UserInput(){};

