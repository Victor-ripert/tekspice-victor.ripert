#pragma once

#include <map>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

#include "IComponent.hpp"
#include "Factory.hpp"
#include "FileReader.hpp"

struct CircuitComponent {
    std::string name;
    std::unique_ptr<nts::IComponent> component;
};

struct NamePin;

class Circuit
{
private:
    std::vector<CircuitComponent> _circuit;
    void sortVector(); // by name;
    // CircuitComponent &getComp();
public:
    Circuit() = default;
    ~Circuit() = default;
    void addComponent(std::string &name, std::string type); // use CompFactory(type); from factory class
    void updateInput(std::string name, nts::Tristate); //only works with type clock or input
    void linkComponents(NamePin pair1, NamePin pair2); // Namepin is just struct with the name as string and pin as size_t
    void printInputs();// need to sort the "_circuit" first;
    void printoutputs();// need to sort the "_circuit" first;

};

std::ostream &operator<<(std::ostream &s, nts::Tristate v);
