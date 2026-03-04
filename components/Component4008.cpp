/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Component4008
*/


#include <memory>

#include "include/components/FullAdderComponent.hpp"
#include "include/components/Component4008.hpp"

namespace nts {
    const std::set<int> Component4008::_input_pins = {1, 2, 3, 4, 5, 6, 7, 9, 15};

    Component4008::Component4008() : AComponent(16, nts::FullAddComp) {
        _components = std::vector<std::unique_ptr<IComponent>>(4);
        _components[0] = std::make_unique<FullAdderComponent>(); // fulladd1
        _components[1] = std::make_unique<FullAdderComponent>(); // fulladd2
        _components[2] = std::make_unique<FullAdderComponent>(); // fulladd3
        _components[3] = std::make_unique<FullAdderComponent>(); // fulladd4
        // fulladd1 = First FullAdder (pin 6 & pin 7 (input of the first bit of each number) & pin 9 (carry_in))
        setOneWayLink(*_components[0], 1, 6);
        setOneWayLink(*_components[0], 2, 7);
        setOneWayLink(*_components[0], 3, 9); // carry
        // fulladd2 = Second FullAdder (pin 4 & pin 5 (idem) & pin 5 of fulladd1 (carry))
        setOneWayLink(*_components[1], 1, 4);
        setOneWayLink(*_components[1], 2, 5);
        _components[1]->setLink(3, *_components[0], 5); // carry : fulladd2 pin3 <-> fulladd1 pin5
        // fulladd3 = Third FullAdder (pin 2 & pin 3 (idem) & pin 5 of fulladd2 (carry))
        setOneWayLink(*_components[2], 1, 2);
        setOneWayLink(*_components[2], 2, 3);
        _components[2]->setLink(3, *_components[1], 5); // carry : fulladd3 pin3 <-> fulladd2 pin5
        // fulladd4 = Forth FullAdder (pin 1 & pin 15 (idem) & pin 5 of fulladd3 (carry))
        setOneWayLink(*_components[3], 1, 1);
        setOneWayLink(*_components[3], 2, 15);
        _components[3]->setLink(3, *_components[2], 5); // carry : fulladd4 pin3 <-> fulladd3 pin5

        // Connected to the output :
        setOneWayLink(*_components[0], 4, 10); // Result of fulladd1 (pin4) -> pin10 (out_0)
        setOneWayLink(*_components[1], 4, 11); // Result of fulladd2 (pin4) -> pin11 (out_1)
        setOneWayLink(*_components[2], 4, 12); // Result of fulladd3 (pin4) -> pin12 (out_2)
        setOneWayLink(*_components[3], 4, 13); // Result of fulladd4 (pin4) -> pin13 (out_3)
        setOneWayLink(*_components[3], 5, 14); // Carry of fulladd4 (pin5) -> pin14 (out_c)
    }

    nts::Tristate Component4008::compute(std::size_t pin) {
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
            case 10:
                _state = this->_components[0]->compute(4);
                break;
            case 11:
                _state = this->_components[1]->compute(4);
                break;
            case 12:
                _state = this->_components[2]->compute(4);
                break;
            case 13:
                _state = this->_components[3]->compute(4);
                break;
            case 14:
                _state = this->_components[3]->compute(5);
                break;
            default:
                _state = nts::Tristate::Undefined;
            }
        }
        _computing = false;
        return _state;
    }
}