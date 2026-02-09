#include "ClockComponent.hpp"

namespace nts{
    nts::Tristate ClockComponent::compute(std::size_t pin) {
        (void)pin;
        return _state;
    }
}
