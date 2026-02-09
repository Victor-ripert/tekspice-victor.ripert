#include "InputComponent.hpp"

namespace nts{
    InputComponent::InputComponent(): AComponent(1, nts::Undefined) {

    };

    nts::Tristate InputComponent::compute(std::size_t pin) {
        (void)pin;
        return _state;
    }
}
