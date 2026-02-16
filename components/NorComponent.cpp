/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** NorComponent
*/


#include <memory>

#include "include/components/OrComponent.hpp"
#include "include/components/NotComponent.hpp"
#include "include/components/NorComponent.hpp"

namespace nts {
    NorComponent::NorComponent() : AComponent(3, nts::NorComp) {
        _components = std::vector<std::unique_ptr<IComponent>>(2);
        _components[0] = std::make_unique<OrComponent>();
        _components[1] = std::make_unique<NotComponent>();
        _components[0]->setLink(1, *this, 1);
        this->_pins[1].component = nullptr;
        this->_pins[1].pin = 0;
        _components[0]->setLink(2, *this, 2);
        this->_pins[2].component = nullptr;
        this->_pins[2].pin = 0;
        _components[1]->setLink(1, *_components[0], 3);
        _components[1]->setLink(2, *this, 3);
        this->_pins[3].component = nullptr;
        this->_pins[3].pin = 0;
    }

    nts::Tristate NorComponent::compute(std::size_t pin) {
        switch (pin)
        {
        case 1:
            return getLink(1);
        case 2:
            return getLink(2);
        case 3:
            return this->_components[1]->compute(2);
        default:
            return nts::Tristate::Undefined;
        }
    }
}