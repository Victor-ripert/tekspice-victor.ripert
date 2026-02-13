#pragma once

#include "AComponent.hpp"


namespace nts {
    class  ClockComponent: public AComponent {
    private:
    public:
        ClockComponent();
        nts::Tristate compute(std::size_t pin) override;
    };
};

