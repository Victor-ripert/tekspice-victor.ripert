/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** FullAdderComponent
*/


#include <memory>

#include "include/components/XorComponent.hpp"
#include "include/components/AndComponent.hpp"
#include "include/components/OrComponent.hpp"
#include "include/components/FullAdderComponent.hpp"

namespace nts {
    const std::set<int> FullAdderComponent::_input_pins = {1, 2, 3};

    FullAdderComponent::FullAdderComponent() : AComponent(5, nts::FullAddComp) {
        _components = std::vector<std::unique_ptr<IComponent>>(5);
        _components[0] = std::make_unique<XorComponent>(); // xor1
        _components[1] = std::make_unique<XorComponent>(); // xor2
        _components[2] = std::make_unique<AndComponent>(); // and1
        _components[3] = std::make_unique<AndComponent>(); // and2
        _components[4] = std::make_unique<OrComponent>();  // or1
        // xor1 = First Xor Gate (pin 1 & 2 (inputs))
        setOneWayLink(*_components[0], 1, 1);
        setOneWayLink(*_components[0], 2, 2);
        // xor2 = Second Xor Gate (pin 3 (carry) and result of xor1)
        setOneWayLink(*_components[1], 1, 3);
        _components[1]->setLink(2, *_components[0], 3); // pin2 of xor2 <-> pin3 of xor1
        // and1 = First And Gate (pin 1 & 2 (inputs))
        setOneWayLink(*_components[2], 1, 1);
        setOneWayLink(*_components[2], 2, 2);
        // and2 = Second And Gate (pin3 (carry) & result of xor1)
        setOneWayLink(*_components[3], 1, 3);
        _components[3]->setLink(2, *_components[0], 3); // pin2 of and2 <-> pin3 of xor1
        // or1 = First Or Gate (result of an1 & result of and2)
        _components[4]->setLink(1, *_components[2], 3); // pin1 of or1 <-> pin3 of and1
        _components[4]->setLink(2, *_components[3], 3); // pin2 of or1 <-> pin3 of and2

        // Connected to the output :
        setOneWayLink(*_components[1], 3, 4); // Result of xor2 with pin4 (result of sum)
        setOneWayLink(*_components[4], 3, 5); // Result of or1 with pin5 (carry)
    }

    nts::Tristate FullAdderComponent::compute(std::size_t pin) {
        if (_computing) {
            if (_input_pins.find(pin) != _input_pins.end())
                return getLink(pin);
            return _state;
        }
        _computing = true;
        if (_input_pins.find(pin) != _input_pins.end()) {
            _state = getLink(pin);
        } else {
            switch (pin) {
            case 4:
                _state = this->_components[1]->compute(3);
                break;
            case 5:
                _state = this->_components[4]->compute(3);
                break;
            default:
                _state = nts::Tristate::Undefined;
            }
        }
        _computing = false;
        return _state;
    }

}