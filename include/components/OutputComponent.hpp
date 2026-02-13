#pragma once

#include "include/components/AComponent.hpp"


namespace nts {
    class  OutputComponent: public AComponent {
    private:
    public:
        OutputComponent();
        nts::Tristate compute(std::size_t pin) override;
    };
};