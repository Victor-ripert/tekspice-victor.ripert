#include "OutputComponent.hpp"

namespace nts{

    OutputComponent::OutputComponent(): AComponent(1) {

    };

    nts::Tristate OutputComponent::compute(std::size_t pin) {
        (void) pin;
        nts::Tristate val1 = getLink(1);
        return val1;
    }
}
