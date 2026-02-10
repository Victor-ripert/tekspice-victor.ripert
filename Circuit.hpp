#pragma once

#include <map>
#include <iostream>
#include "IComponent.hpp"
#include <tuple>
#include <vector>
#include <algorithm>
#include <string>

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
    void addComponent(std::string name, std::string type); // need to make fac to sort
    void updateInput(std::string name, nts::Tristate); //only works with type clock or input
    void printInputs();// need to sort the "_circuit" first;
    void printoutputs();// need to sort the "_circuit" first;
    ~Circuit();
};
