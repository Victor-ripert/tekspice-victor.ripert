/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** NandComponent
*/


#include <memory>

#include "include/components/AndComponent.hpp"
#include "include/components/NotComponent.hpp"
#include "include/components/NandComponent.hpp"

namespace nts {
    NandComponent::NandComponent() : AComponent(3, nts::NandComp) {
        _components = std::vector<std::unique_ptr<IComponent>>(2);
        _components[0] = std::make_unique<AndComponent>();
        _components[1] = std::make_unique<NotComponent>();
        setOneWayLink(*_components[0], 1, 1);
        setOneWayLink(*_components[0], 2, 2);
        _components[1]->setLink(1, *_components[0], 3);
        setOneWayLink(*_components[1], 2, 3);
    }

    nts::Tristate NandComponent::compute(std::size_t pin) {
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