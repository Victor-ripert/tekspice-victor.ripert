/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** FullAdderComponent
*/

#ifndef FULLADDERCOMPONENT_HPP
    #define FULLADDERCOMPONENT_HPP
    #include "include/components/AComponent.hpp"
    #include <memory>
    #include <set>

namespace nts {
    class FullAdderComponent : public AComponent {
        private:
        std::vector<std::unique_ptr<IComponent>> _components;
        static const std::set<int> _input_pins;

        public:
            FullAdderComponent();
            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* FULLADDERCOMPONENT_HPP */