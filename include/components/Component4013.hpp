/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** Component4013
*/

#ifndef COMPONENT4013_HPP
    #define COMPONENT4013_HPP
    #include "include/components/AComponent.hpp"
    #include <memory>
    #include <set>

namespace nts {
    class Component4013 : public AComponent {
        private:
        std::vector<std::unique_ptr<IComponent>> _components;
        static const std::set<int> _input_pins;

        public:
            Component4013();
            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENT4013_HPP */