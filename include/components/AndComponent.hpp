#pragma once

#include "include/components/AComponent.hpp"


namespace nts {
    class  AndComponent: public AComponent {
    private:
    public:
        AndComponent();
        nts::Tristate compute(std::size_t pin) override;
    };
};

