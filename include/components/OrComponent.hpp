#pragma once

#include "include/components/AComponent.hpp"


namespace nts {
    class  OrComponent: public AComponent {
    private:
    public:
        OrComponent();
        nts::Tristate compute(std::size_t pin) override;
    };
};

