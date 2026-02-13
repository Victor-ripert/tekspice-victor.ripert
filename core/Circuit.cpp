#include "include/core/Circuit.hpp"
#include "include/components/AndComponent.hpp"
#include "include/components/AComponent.hpp"
#include "include/core/NanoTekSpiceExceptions.hpp"
#include <algorithm>



// std::vector<CircuitComponent> _circuit;
// void sortVector(); // by name;

// struct CircuitComponent {
//     std::string name;
//     nts::IComponent *component;
// };

// struct NamePin {
//     std::string name;
//     size_t pin;
// };

Circuit::Circuit():_tick(0){
}


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
    // std::cout << "ADDED COMP" << std::endl;
    CompFactory factory;
    CircuitComponent newComp;
    // nts::AndComponent needFac;
    //Need TO ADD IN FACTORY HERE;
    newComp.component = factory.createComponent(type);
    newComp.name = name;
    _circuit.push_back(std::move(newComp));
} // use CompFactory(type); from factory class

void  Circuit::linkComponents(NamePin pair1, NamePin pair2){
    auto currentComp1 = std::find_if(_circuit.begin(), _circuit.end(), [&pair1](const CircuitComponent& cur) {
        return cur.name == pair1.name;
    });
    auto currentComp2 = std::find_if(_circuit.begin(), _circuit.end(), [&pair2](const CircuitComponent& cur) {
        return cur.name == pair2.name;
    });

    if (currentComp1 == _circuit.end() || currentComp2 == _circuit.end()) {
        throw nts::NanoExecption("Couldn't find the right component");
        return;
    }

    currentComp1->component->setLink(pair1.pin, *currentComp2->component, pair2.pin);
}; // Namepin is just struct with the name as string and pin as size_t


void Circuit::updateInput(std::string name, nts::Tristate state) {
    auto currentComp = std::find_if(_circuit.begin(), _circuit.end(), [&name](const CircuitComponent& cur) {
        return cur.name == name;
    });

    if (currentComp == _circuit.end()) {
        throw nts::NanoExecption("Couldn't find the right component");
        return;
    }

    if ((*currentComp).component->getType() == nts::ClockComp || (*currentComp).component->getType() == nts::InputComp) {
        (*currentComp).component->setTristate(state);
    }
}; //only works with type clock or input

bool inputCheck(nts::IComponent &comp) {
    if(comp.getType() == nts::ClockComp
    || comp.getType() == nts::InputComp
    || comp.getType() == nts::TrueComp
    || comp.getType() == nts::FalseComp
    ) {
        return true;
    }
    return false;
}

void Circuit::printInputs(){
    if (!(std::is_sorted(_circuit.begin(), _circuit.end(), CircuitNameComp))) {
        sortVector();
    }
    for (size_t i = 0; i < _circuit.size(); i++) {
        if (!_circuit[i].component) {
            std::cerr << "Error: null component at index " << i << std::endl;
            continue;
        }
        if (inputCheck(*_circuit[i].component)) { // need to add the other type in a smart way // Truetype, False, Clock.
        std::cout << "\t" <<_circuit[i].name << ": " << _circuit[i].component->compute(1) << std::endl;
        };
    }
};// need to sort the "_circuit" first;

void Circuit::printoutputs(){
    if (!(std::is_sorted(_circuit.begin(), _circuit.end(), CircuitNameComp))) {
        sortVector();
    }
    for (size_t i = 0; i < _circuit.size(); i++) {
        if (_circuit[i].component->getType() == nts::OutputComp ) { // need to add the other type in a smart way - i guess only Output maybe
        std::cout << "\t" <<_circuit[i].name << ": " << _circuit[i].component->compute(1) << std::endl;
        };
    }
};// need to sort the "_circuit" first;

void updateClock(nts::IComponent &clock) {
    if (clock.getTristate() == nts::Undefined)
        return;
    if(clock.getTristate() == nts::True) {
        clock.setTristate(nts::False);
    } else {
        clock.setTristate(nts::True);
    }
}

void Circuit::oneTick() {
    _tick = _tick + 1;
    for (size_t i = 0; i < _circuit.size(); i++) {
        if (_circuit[i].component->getType() == nts::ClockComp ) { // update
            updateClock(*_circuit[i].component);
        };
    }
}

size_t Circuit::getTick() {
    return _tick;
}