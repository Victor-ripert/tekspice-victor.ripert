/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** 4001Component
*/

#ifndef COMPONENT4001_HPP
    #define COMPONENT4001_HPP
    #include "include/components/AComponent.hpp"
    #include <memory>

namespace nts {
    class Component4001 : public AComponent {
        private:
        std::vector<std::unique_ptr<IComponent>> _components;

        public:
            Component4001();
            nts::Tristate compute(std::size_t pin) override;
            void setOneWayLink(std::size_t wichComponent, std::size_t pin, std::size_t otherPin);
            void setOneWayLink2(std::unique_ptr<IComponent> component, std::size_t pin, std::size_t otherPin)
    };
}

#endif /* COMPONENT4001_HPP */