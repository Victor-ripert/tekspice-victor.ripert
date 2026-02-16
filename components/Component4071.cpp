#include "include/components/Component4071.hpp"

namespace nts{
    const std::set<int> Component4071::_input_pins = {1, 2, 5, 6, 8, 9, 12, 13};

    Component4071::Component4071() : AComponent(14, nts::Comp4071) {
        for(int i = 0; i < 4; i++) {
            _orGates[i] = std::make_unique<OrComponent>();
        }
        // First Nor Gate
        setOneWayLink(*_orGates[0], 1, 1); // Input 1
        setOneWayLink(*_orGates[0], 2, 2); // Input 2
        setOneWayLink(*_orGates[0], 3, 3); // Output
        // Second Nor Gate
        setOneWayLink(*_orGates[1], 1, 5); // Input 1
        setOneWayLink(*_orGates[1], 2, 6); // Input 2
        setOneWayLink(*_orGates[1], 3, 4); // Output
        // Third Nor Gate
        setOneWayLink(*_orGates[2], 1, 8); // Input 1
        setOneWayLink(*_orGates[2], 2, 9); // Input 2
        setOneWayLink(*_orGates[2], 3, 10); // Output
        // Forth Nor Gate
        setOneWayLink(*_orGates[3], 1, 12); // Input 1
        setOneWayLink(*_orGates[3], 2, 13); // Input 2
        setOneWayLink(*_orGates[3], 3, 11); // Output
        // Pin 7 & 14 are ignored for this project;
    }

    nts::Tristate Component4071::compute(std::size_t pin) {
        if (_input_pins.find(pin) != _input_pins.end())
            return getLink(pin); // Input
        switch (pin) { //otput
            case 3:
                return this->_orGates[0]->compute(3);
            case 4:
                return this->_orGates[1]->compute(3);
            case 10:
                return this->_orGates[2]->compute(3);
            case 11:
                return this->_orGates[3]->compute(3);
            default: // Pin 7, 14 and error returns Undefined
                return nts::Tristate::Undefined;
        }
    }
}

