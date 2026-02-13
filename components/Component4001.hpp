/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** 4001Component
*/

#ifndef COMPONENT4001_HPP
    #define COMPONENT4001_HPP
    #include "AComponent.hpp"

namespace nts {
    class Component4001 : public AComponent {
        private:
        std::vector<IComponent> _components;
        public:
            Component4001();
            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENT4001_HPP */