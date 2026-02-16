#pragma once

#include "include/components/AComponent.hpp"
#include "include/components/OrComponent.hpp"
#include "include/components/NotComponent.hpp"
#include <array>
#include <memory>
#include <set>


namespace nts {
    class  Component4069: public AComponent {
    private:
        std::array<std::unique_ptr<NotComponent>, 6> _notGates;
        static const std::set<int> _input_pins;
    public:
    Component4069();
        nts::Tristate compute(std::size_t pin) override;
    };
};

