#pragma once

#include "AComponent.hpp"


namespace nts {
    class  FalseComponent: public AComponent {
    private:
    public:
        FalseComponent();
        nts::Tristate compute(std::size_t pin) override;
    };
};

