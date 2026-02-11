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

// struct NamePin {
//     std::string name;
//     size_t pin;
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
        //need error couldnt find;
        return;
    }

    currentComp1->component->setLink(pair1.pin, *currentComp2->component, pair2.pin);
}; // Namepin is just struct with the name as string and pin as size_t


void Circuit::updateInput(std::string name, nts::Tristate state) {
    auto currentComp = std::find_if(_circuit.begin(), _circuit.end(), [&name](const CircuitComponent& cur) {
        return cur.name == name;
    });

    if (currentComp == _circuit.end()) {
        //need error couldnt find;
        return;
    }

    if ((*currentComp).component->getType() == nts::ClockComp || (*currentComp).component->getType() == nts::InputComp) {
        (*currentComp).component->setTristate(state);
    }
}; //only works with type clock or input


void Circuit::printInputs(){

    if (!(std::is_sorted(_circuit.begin(), _circuit.end(), CircuitNameComp))) {
        sortVector();
    }
    for (size_t i = 0; i < _circuit.size(); i++) {
        if (_circuit[i].component->getType() == nts::InputComp ) { // need to add the other type in a smart way // Truetype, False, Clock.
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
