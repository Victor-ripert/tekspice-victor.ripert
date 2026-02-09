#include "FalseComponent.hpp"

namespace nts{

    FalseComponent::FalseComponent(): AComponent(1, nts::False) {

    };
    nts::Tristate FalseComponent::compute(std::size_t pin) {
        (void) pin;
        return nts::False;
    };
}
