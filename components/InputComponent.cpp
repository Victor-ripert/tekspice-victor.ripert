#include "include/components/InputComponent.hpp"

namespace nts{
    InputComponent::InputComponent(): AComponent(1, nts::InputComp, nts::Undefined) {

    };

    nts::Tristate InputComponent::compute(std::size_t pin) {
        (void)pin;
        return _state;
    }
}
