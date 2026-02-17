/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** Component4008
*/

#ifndef COMPONENT4008_HPP
    #define COMPONENT4008_HPP
    #include "include/components/AComponent.hpp"
    #include <memory>
    #include <set>

namespace nts {
    class Component4008 : public AComponent {
        private:
        std::vector<std::unique_ptr<IComponent>> _components;
        static const std::set<int> _input_pins;

        public:
            Component4008();
            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENT4008_HPP */