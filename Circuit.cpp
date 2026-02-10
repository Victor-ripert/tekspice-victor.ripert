#include "Circuit.hpp"
#include "AndComponent.hpp"
#include "AComponent.hpp"
#include <algorithm>



// std::vector<CircuitComponent> _circuit;
// void sortVector(); // by name;

// struct CircuitComponent {
//     std::string name;
//     nts::IComponent *component;
// };


std::ostream &operator<<(std::ostream &s, nts::Tristate v)
{
    switch (v) {
    case nts::Undefined:
        s << "U";
        break;
    case nts::True:
        s << "1";
        break;
    case nts::False:
        s << "0";
        break;
    default:
        break;
    }
    return s;
}

bool CircuitNameComp(const CircuitComponent &a, const CircuitComponent &b) {
    return a.name < b.name;
}
void Circuit::sortVector() {
    std::sort(_circuit.begin(), _circuit.end(), CircuitNameComp);
}
// Circuit();
void Circuit::addComponent(std::string &name, std::string type) {

    CircuitComponent newComp;
    nts::AndComponent needFac;
    //Need TO ADD IN FACTORY HERE;
    newComp.component = &needFac;
    newComp.name = name;
    _circuit.push_back(newComp);
} // use CompFactory(type); from factory class


void Circuit::updateInput(std::string name, nts::Tristate state) {

auto currentComp = std::find_if(_circuit.begin(), _circuit.end(), [&name](const CircuitComponent& cur) {
    return cur.name == name;
});

if (currentComp == _circuit.end()) {
    //need error couldnt find;
    return;
}

if ((*currentComp).component->getType() == nts::Clock || (*currentComp).component->getType() == nts::Input) {
    (*currentComp).component->setTristate(state);
}
}; //only works with type clock or input


void Circuit::printInputs(){

    if (!(std::is_sorted(_circuit.begin(), _circuit.end(), CircuitNameComp))) {
        sortVector();
    }
    for (size_t i = 0; i < _circuit.size(); i++) {
        if (_circuit[i].component->getType() == nts::Input) { // need to add the other type in a smart way // Truetype, False, Clock.
        std::cout << "\t" <<_circuit[i].name << ": " << _circuit[i].component->compute(1) << std::endl;
        };
    }
};// need to sort the "_circuit" first;

void Circuit::printoutputs(){
    if (!(std::is_sorted(_circuit.begin(), _circuit.end(), CircuitNameComp))) {
        sortVector();
    }
    for (size_t i = 0; i < _circuit.size(); i++) {
        if (_circuit[i].component->getType() == nts::Output) { // need to add the other type in a smart way - i guess only Output maybe
        std::cout << "\t" <<_circuit[i].name << ": " << _circuit[i].component->compute(1) << std::endl;
        };
    }
};// need to sort the "_circuit" first;

Circuit::~Circuit() {
    for (auto& comp : _circuit) {
        delete comp.component;
    }
}
