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
    };
}

#endif /* COMPONENT4001_HPP */