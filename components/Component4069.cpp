#include "include/components/Component4069.hpp"

namespace nts{
    const std::set<int> Component4069::_input_pins = {1, 3, 5, 9, 11, 13};

    Component4069::Component4069() : AComponent(14, nts::Comp4069) {
        for(int i = 0; i < 6; i++) {
            _notGates[i] = std::make_unique<NotComponent>();
        }
        // First Nor
        setOneWayLink(*_notGates[0], 1, 1); // Input 1
        setOneWayLink(*_notGates[0], 2, 2); // Input 2
        // Second Nor
        setOneWayLink(*_notGates[1], 1, 3); // Input 1
        setOneWayLink(*_notGates[1], 2, 4); // Input 2
        // Third Nor
        setOneWayLink(*_notGates[2], 1, 5); // Input 1
        setOneWayLink(*_notGates[2], 2, 6); // Input 2
        // Forth Nor
        setOneWayLink(*_notGates[3], 1, 9); // Input 1
        setOneWayLink(*_notGates[3], 2, 8); // Input 2

        setOneWayLink(*_notGates[4], 1, 11); // Input 1
        setOneWayLink(*_notGates[4], 2, 10); // Input 2

        setOneWayLink(*_notGates[5], 1, 13); // Input 1
        setOneWayLink(*_notGates[5], 2, 12); // Input 2
        // Pin 7 & 14 ed for this project;
    }

    nts::Tristate Component4069::compute(std::size_t pin) {
        if (_input_pins.find(pin) != _input_pins.end())
            return getLink(pin); // Input
        switch (pin) { //otput
            case 2:
                return this->_notGates[0]->compute(2);
            case 4:
                return this->_notGates[1]->compute(2);
            case 6:
                return this->_notGates[2]->compute(2);
            case 8:
                return this->_notGates[3]->compute(2);
            case 10:
                return this->_notGates[4]->compute(2);
            case 12:
                return this->_notGates[5]->compute(2);
            default: // Pin 7, 14 and error returns Undefined
                return nts::Tristate::Undefined;
        }
    }
}

