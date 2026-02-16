/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** 4001Component
*/

#ifndef NORCOMPONENT_HPP
    #define NORCOMPONENT_HPP
    #include "include/components/AComponent.hpp"
    #include <memory>

namespace nts {
    class NorComponent : public AComponent {
        private:
        std::vector<std::unique_ptr<IComponent>> _components;

        public:
            NorComponent();
            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* NORCOMPONENT_HPP */