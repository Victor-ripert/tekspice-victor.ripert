#pragma once

#include "include/components/AComponent.hpp"
#include "include/components/OrComponent.hpp"
#include <array>
#include <memory>
#include <set>


namespace nts {
    class  Component4071: public AComponent {
    private:
        std::array<std::unique_ptr<OrComponent>, 4> _orGates;
        static const std::set<int> _input_pins;
    public:
        Component4071();
        nts::Tristate compute(std::size_t pin) override;
    };
};

