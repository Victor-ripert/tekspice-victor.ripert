#include "OutputComponent.hpp"

namespace nts{

    OutputComponent::OutputComponent(): AComponent(1, nts::OutputComp) {

    };

    nts::Tristate OutputComponent::compute(std::size_t pin) {
        (void) pin;
        return getLink(1);
    }
}
