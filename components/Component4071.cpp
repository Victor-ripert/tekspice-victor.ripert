#include "include/components/Component4071.hpp"

namespace nts{
    Component4071::Component4071() : AComponent(14, nts::Comp4071) {

        for(int i = 0; i < 4; i++) {
            _orGates[i] = std::make_unique<OrComponent>();
        }
    };

    nts::Tristate Component4071::compute(std::size_t pin) {
        if (pin == 1 || pin == 2) {
            return getLink(pin);
        }
        if (pin == 3) {
            _orGates[0]->getPin(1) = _pins[1];
            _orGates[0]->getPin(2) = _pins[2];

            return _orGates[0]->compute(3);
        }
        if (pin == 5 || pin == 6) {
            return getLink(pin);
        }
        if (pin == 4) {
            _orGates[1]->getPin(1) = _pins[5];
            _orGates[1]->getPin(2) = _pins[6];

            return _orGates[1]->compute(3);
        }
        if (pin == 8 || pin == 9) {
            return getLink(pin);
        }
        if (pin == 10) {
            _orGates[2]->getPin(1) = _pins[8];
            _orGates[2]->getPin(2) = _pins[9];

            return _orGates[2]->compute(3);
        }
        if (pin == 12|| pin == 13) {
            return getLink(pin);
        }
        if (pin == 11) {
            _orGates[3]->getPin(1) = _pins[12];
            _orGates[3]->getPin(2) = _pins[13];

            return _orGates[3]->compute(3);
        }
        return Undefined;
    }
}


