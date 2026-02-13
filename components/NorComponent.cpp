/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** NorComponent
*/


#include "NorComponent.hpp"
#include "OrComponent.hpp"
#include "NotComponent.hpp"
#include <memory>

namespace nts {
    NorComponent::NorComponent() : AComponent(3, nts::NorComp) {
        std::vector<IComponent> components;
        std::unique_ptr<IComponent> or_gate = std::make_unique<OrComponent>();
        std::unique_ptr<IComponent> not_gate = std::make_unique<NotComponent>();
        components.push_back(*or_gate);
        or_gate->setLink(1, *this, 1);
        this->_pins[1].component = nullptr;
        this->_pins[1].pin = 0;
        or_gate->setLink(2, *this, 2);
        this->_pins[2].component = nullptr;
        this->_pins[2].pin = 0;
        not_gate->setLink(1, *or_gate, 3);
        not_gate->setLink(2, *this, 3);
        this->_pins[3].component = nullptr;
        this->_pins[3].pin = 0;
    }
}