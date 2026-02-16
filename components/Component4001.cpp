/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** NorComponent
*/


#include <memory>

#include "include/components/NorComponent.hpp"
#include "include/components/Component4001.hpp"

namespace nts {
    Component4001::Component4001() : AComponent(14, nts::Comp4001) {
        _components = std::vector<std::unique_ptr<IComponent>>(4);
        _components[0] = std::make_unique<NorComponent>();
        _components[1] = std::make_unique<NorComponent>();
        _components[2] = std::make_unique<NorComponent>();
        _components[3] = std::make_unique<NorComponent>();
        // First Nor Gate
        setOneWayLink(0, 1, 1); // Input 1
        setOneWayLink(0, 2, 2); // Input 2
        setOneWayLink(0, 3, 3); // Output
        // Second Nor Gate
        setOneWayLink(1, 1, 5); // Input 1
        setOneWayLink(1, 2, 6); // Input 2
        setOneWayLink(1, 3, 4); // Output
        // Third Nor Gate
        setOneWayLink(2, 1, 8); // Input 1
        setOneWayLink(2, 2, 9); // Input 2
        setOneWayLink(2, 3, 10); // Output
        // Forth Nor Gate
        setOneWayLink(3, 1, 12); // Input 1
        setOneWayLink(3, 2, 13); // Input 2
        setOneWayLink(3, 3, 11); // Output
        // Pin 7 & 14 are ignored for this project;
    }

    void Component4001::setOneWayLink(std::size_t wichComponent, std::size_t pin, std::size_t otherPin) {
        _components[wichComponent]->setLink(pin, *this, otherPin);
        this->_pins[otherPin].component = nullptr;
        this->_pins[otherPin].pin = 0;
    }

    void Component4001::setOneWayLink2(std::unique_ptr<IComponent> component, std::size_t pin, std::size_t otherPin) {
        component->setLink(pin, *this, otherPin);
        this->_pins[otherPin].component = nullptr;
        this->_pins[otherPin].pin = 0;
    }

    nts::Tristate Component4001::compute(std::size_t pin) {
        switch (pin) {
        // Nor Gate 1
        case 1: // Input
            return getLink(1);
        case 2: // Input
            return getLink(2);
        case 3: // Output
            return this->_components[0]->compute(3);
        // Nor Gate 2
        case 4: // OutPut
            return this->_components[1]->compute(3);
        case 5: // Input
            return getLink(5);
        case 6: // Input
            return getLink(6);
        // Nor Gate 3
        case 8: // Input
            return getLink(8);
        case 9: // Input
            return getLink(9);
        case 10: // Output
            return this->_components[2]->compute(3);
        // Nor Gate 4
        case 11: // OutPut
            return this->_components[3]->compute(3);
        case 12: // Input
            return getLink(12);
        case 13: // Input
            return getLink(13);
        default: // Pin 7, 14 and error returns Undefined
            return nts::Tristate::Undefined;
        }
    }
}