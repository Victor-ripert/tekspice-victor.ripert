/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** DFlipFlopComponent
*/

#ifndef DFLIPFLOPCOMPONENT_HPP
    #define DFLIPFLOPCOMPONENT_HPP
    #include "include/components/AComponent.hpp"
    #include <memory>
    #include <set>

namespace nts {
    class DFlipFlopComponent : public AComponent {
        private:
        std::vector<std::unique_ptr<IComponent>> _components;
        static const std::set<int> _input_pins;

        public:
            DFlipFlopComponent();
            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* DFLIPFLOPCOMPONENT_HPP */