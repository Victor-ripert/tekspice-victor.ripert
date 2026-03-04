/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Component4011
*/


#include <memory>

#include "include/components/NandComponent.hpp"
#include "include/components/Component4011.hpp"

namespace nts {
    const std::set<int> Component4011::_input_pins = {1, 2, 5, 6, 8, 9, 12, 13};

    Component4011::Component4011() : AComponent(14, nts::Comp4011) {
        _components = std::vector<std::unique_ptr<IComponent>>(4);
        _components[0] = std::make_unique<NandComponent>();
        _components[1] = std::make_unique<NandComponent>();
        _components[2] = std::make_unique<NandComponent>();
        _components[3] = std::make_unique<NandComponent>();
        // First Nor Gate
        setOneWayLink(*_components[0], 1, 1); // Input 1
        setOneWayLink(*_components[0], 2, 2); // Input 2
        setOneWayLink(*_components[0], 3, 3); // Output
        // Second Nor Gate
        setOneWayLink(*_components[1], 1, 5); // Input 1
        setOneWayLink(*_components[1], 2, 6); // Input 2
        setOneWayLink(*_components[1], 3, 4); // Output
        // Third Nor Gate
        setOneWayLink(*_components[2], 1, 8); // Input 1
        setOneWayLink(*_components[2], 2, 9); // Input 2
        setOneWayLink(*_components[2], 3, 10); // Output
        // Forth Nor Gate
        setOneWayLink(*_components[3], 1, 12); // Input 1
        setOneWayLink(*_components[3], 2, 13); // Input 2
        setOneWayLink(*_components[3], 3, 11); // Output
        // Pin 7 & 14 are ignored for this project;
    }

    nts::Tristate Component4011::compute(std::size_t pin) {
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
            case 3:
                _state = this->_components[0]->compute(3);
                break;
            case 4:
                _state = this->_components[1]->compute(3);
                break;
            case 10:
                _state = this->_components[2]->compute(3);
                break;
            case 11:
                _state = this->_components[3]->compute(3);
                break;
            default:
                _state = nts::Tristate::Undefined;
            }
        }
        _computing = false;
        return _state;
    }

}