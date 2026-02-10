#pragma once

#include "IComponent.hpp"
#include <vector>


namespace nts {
    struct PinLink {
        IComponent *component;
        std::size_t pin;
        PinLink() : component(nullptr), pin(0) {}
    };

    class AComponent : public IComponent {
    protected:
        nts::Tristate _state;
        std::vector<PinLink> _pins;
        size_t _number_of_pins;
        nts::CompType _compType;
    public:
        AComponent(size_t pins, nts::Tristate state = nts::Undefined);
        // void simulate(std::size_t tick)override;
        // nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        nts::Tristate getLink(std::size_t pin) override;
        nts::CompType getType() override;
        void setType(nts::CompType type) override;
        void setTristate(nts::Tristate state) override;
    };
};

