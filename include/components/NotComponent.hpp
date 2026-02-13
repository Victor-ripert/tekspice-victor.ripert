#pragma once

#include "include/components/AComponent.hpp"


namespace nts {
    class  NotComponent: public AComponent {
    private:
    public:
        NotComponent();
        nts::Tristate compute(std::size_t pin) override;
    };
};

