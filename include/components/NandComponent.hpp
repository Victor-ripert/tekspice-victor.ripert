/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** NandComponent
*/

#ifndef NANDCOMPONENT_HPP
    #define NANDCOMPONENT_HPP
    #include "include/components/AComponent.hpp"
    #include <memory>

namespace nts {
    class NandComponent : public AComponent {
        private:
        std::vector<std::unique_ptr<IComponent>> _components;

        public:
            NandComponent();
            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* NANDCOMPONENT_HPP */