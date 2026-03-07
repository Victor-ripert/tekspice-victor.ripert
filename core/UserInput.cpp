#include "include/core/UserInput.hpp"
#include <algorithm>
#include <csignal>
#include <iostream>
#include "include/core/NanoTekSpiceExceptions.hpp"

static volatile sig_atomic_t _sigint = 0;

static void _sigHandler(int) {
    _sigint = 1;
}


UserInput::UserInput(Circuit &circuit) : _circuit(circuit) {
    _map["display"]  = [this]() { _Display(); };
    _map["simulate"] = [this]() { _Simulate(); };
    _map["loop"]     = [this]() { _Loop(); };
}


static nts::Tristate getState(const std::string &val) {
    if (val == "0")
        return nts::False;
    if (val == "1")
        return nts::True;
    if (val == "U")
        return nts::Undefined;
    throw nts::NanoExecption(
        ("Invalid value '" + val + "': expected 0, 1, or U").c_str()
    );
}


void UserInput::updateVal(const std::string &line) {
    size_t pos = line.find('=');
    if (pos == std::string::npos)
        throw nts::NanoExecption(
            ("Unknown command: '" + line + "'").c_str()
        );

    std::string name  = line.substr(0, pos);
    std::string value = line.substr(pos + 1);

    if (name.empty())
        throw nts::NanoExecption("Invalid assignment: input name cannot be empty");
    if (value.empty())
        throw nts::NanoExecption(
            ("Invalid assignment: missing value for input '" + name + "'").c_str()
        );

    nameVal nv;
    nv.name  = name;
    nv.state = getState(value);
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
    while (true) {
        std::cout << "> ";
        std::cout.flush();

        if (!std::getline(std::cin, _input))
            break;

        size_t start = _input.find_first_not_of(" \t\r\n");
        if (start == std::string::npos)
            continue;
        _input = _input.substr(start, _input.find_last_not_of(" \t\r\n") - start + 1);

        if (_input.empty())
            continue;
        if (_input == "exit")
            break;

        try {
            auto it = _map.find(_input);
            if (it != _map.end())
                it->second();
            else
                updateVal(_input);
        } catch (const nts::NanoExecption &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}


UserInput::~UserInput() {}