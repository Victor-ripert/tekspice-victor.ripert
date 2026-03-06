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
        setOneWayLink(*_components[0], 1, 1);
        setOneWayLink(*_components[0], 2, 2);
        _components[1]->setLink(1, *_components[0], 3);
        setOneWayLink(*_components[1], 2, 3);
    }

    nts::Tristate NorComponent::compute(std::size_t pin) {
        if (_computing) {
            if (pin == 1 || pin == 2)
                return getLink(pin);
            return _state;
        }
        _computing = true;
        switch (pin) {
        case 1:
            _state = getLink(1);
            break;
        case 2:
            _state = getLink(2);
            break;
        case 3:
            _state = this->_components[1]->compute(2);
            break;
        default:
            _state = nts::Tristate::Undefined;
        }
        _computing = false;
        return _state;
    }

}