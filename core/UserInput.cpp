#include "include/core/UserInput.hpp"
#include <algorithm>
#include <csignal>
#include <iostream>

static volatile sig_atomic_t _sigint = 0;

static void _sigHandler(int) {
    _sigint = 1;
}


UserInput::UserInput(Circuit &circuit) : _circuit(circuit) {
    _map["display"]  = [this]() { _Display(); };
    _map["simulate"] = [this]() { _Simulate(); };
    _map["loop"]     = [this]() { _Loop(); };
}


nts::Tristate getState(const std::string &val) {
    if (val == "0")
        return nts::False;
    if (val == "1")
        return nts::True;
    return nts::Undefined;
}


void UserInput::updateVal(const std::string &line) {
    size_t pos = line.find('=');
    if (pos == std::string::npos)
        return;
    nameVal nv;
    nv.name  = line.substr(0, pos);
    nv.state = getState(line.substr(pos + 1));
    updateQueue.push(nv);
}


void UserInput::_Display() {
    std::cout << "tick: " << _circuit.getTick() << std::endl;
    std::cout << "input(s):" << std::endl;
    _circuit.printInputs();
    std::cout << "output(s):" << std::endl;
    _circuit.printoutputs();
}


void UserInput::_Simulate() {
    while (!updateQueue.empty()) {
        nameVal temp = updateQueue.front();
        updateQueue.pop();
        _circuit.updateInput(temp.name, temp.state);
    }
    _circuit.oneTick();
}


void UserInput::_Loop() {
    _sigint = 0;
    std::signal(SIGINT, _sigHandler);
    while (!_sigint) {
        _Simulate();
        _Display();
    }
    std::signal(SIGINT, SIG_DFL);
    std::cout << std::endl;
}


void UserInput::runInputs() {
    do {
        std::cout << "> ";
        if (!(std::cin >> _input))
            break;
        auto it = _map.find(_input);
        if (it != _map.end())
            it->second();
        else
            updateVal(_input);
    } while (_input != "exit");
}


UserInput::~UserInput() {}
