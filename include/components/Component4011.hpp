/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** 4011Component
*/

#ifndef COMPONENT4011_HPP
    #define COMPONENT4011_HPP
    #include "include/components/AComponent.hpp"
    #include <memory>
    #include <set>

namespace nts {
    class Component4011 : public AComponent {
        private:
        std::vector<std::unique_ptr<IComponent>> _components;
        static const std::set<int> _input_pins;

        public:
            Component4011();
            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENT4011_HPP */