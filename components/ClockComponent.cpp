#include "include/components/ClockComponent.hpp"

namespace nts{

    ClockComponent::ClockComponent() : AComponent(1, nts::ClockComp) {};
    
    nts::Tristate ClockComponent::compute(std::size_t pin) {
        (void)pin;
        return _state;
    }
}
