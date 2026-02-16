/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** 4081Component
*/

#ifndef COMPONENT4081_HPP
    #define COMPONENT4081_HPP
    #include "include/components/AComponent.hpp"
    #include <memory>
    #include <set>

namespace nts {
    class Component4081 : public AComponent {
        private:
        std::vector<std::unique_ptr<IComponent>> _components;
        static const std::set<int> _input_pins;

        public:
            Component4081();
            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENT4081_HPP */