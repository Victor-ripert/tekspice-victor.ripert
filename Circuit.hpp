#pragma once

#include <map>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <string>

#include "IComponent.hpp"
#include "Factory.hpp"

struct CircuitComponent {
    std::string name;
    nts::IComponent *component;
};

class Circuit
{
private:
    std::vector<CircuitComponent> _circuit;
    void sortVector(); // by name;
public:
    Circuit();
    void addComponent(std::string name, std::string type); // use CompFactory(type); from factory class
    void updateInput(std::string name, nts::Tristate); //only works with type clock or input
    void printInputs();// need to sort the "_circuit" first;
    void printoutputs();// need to sort the "_circuit" first;
    ~Circuit();
};
