#include "AComponent.hpp"
#include<iostream>

namespace nts {

    AComponent::AComponent(size_t pins, nts::CompType type, nts::Tristate state)
    : _state(state), _pins(pins), _number_of_pins(pins), _compType(type){
        _pins.resize(pins + 1);
    };

    void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) {
        if (pin >= _pins.size() || pin == 0 || otherPin == 0) return;
        _pins[pin].component = &other;
        _pins[pin].pin = otherPin;

        auto *otherComp = dynamic_cast<AComponent*>(&other);
        if (otherComp && otherPin < otherComp->_pins.size()) {
            otherComp->_pins[otherPin].component = this;
            otherComp->_pins[otherPin].pin = pin;
        };
    };

    nts::Tristate AComponent::getLink(std::size_t pin) {
        if (pin >= _pins.size()) {
            return nts::Undefined;
        }
        if (_pins[pin].component == nullptr) {
            return nts::Undefined;
        }
        return _pins[pin].component->compute(_pins[pin].pin);
    }

    nts::CompType AComponent::getType() {
        return _compType;
    }

    void AComponent::setType(nts::CompType type) {
        _compType = type;
    }

    void AComponent::setTristate(nts::Tristate state) {
        _state = state;
    }

    nts::Tristate AComponent::getTristate() {
        return _state;
    };
};