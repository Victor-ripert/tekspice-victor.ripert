#pragma once

#include "AComponent.hpp"


namespace nts {
    class  InputComponent: public AComponent {
    private:
    public:
        InputComponent();
        nts::Tristate compute(std::size_t pin) override;
    };
};

