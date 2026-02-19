#pragma once

#include "include/core/Circuit.hpp"
#include <iostream>
#include <unordered_map>
#include <functional>
#include "include/components/IComponent.hpp"
#include <queue>

struct nameVal{
    std::string name;
    nts::Tristate state;
};

class UserInput
{
private:
    std::string _input;
    std::queue <nameVal> updateQueue;
    std::unordered_map<std::string, std::function<void()>> _map;
    Circuit &_circuit;
    void _Exit();
    void _Display();
    void _Simulate();
    void _Loop();
    void _UpdateVal(std::string name, nts::Tristate val);
    void updateVal(std::string line);

public:
    UserInput(Circuit &);
    void runInputs();
    ~UserInput();
};
