#pragma once

#include "include/components/AComponent.hpp"


namespace nts {
    class  TrueComponent: public AComponent {
    private:
    public:
        TrueComponent();
        nts::Tristate compute(std::size_t pin) override;
    };
};

