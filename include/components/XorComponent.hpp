#pragma once

#include "include/components/AComponent.hpp"


namespace nts {
    class  XorComponent: public AComponent {
    private:
    public:
        XorComponent();
        nts::Tristate compute(std::size_t pin) override;
    };
};

