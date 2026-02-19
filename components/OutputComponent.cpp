#include "include/components/OutputComponent.hpp"

namespace nts{

    OutputComponent::OutputComponent(): AComponent(1, nts::OutputComp) {

    };

    nts::Tristate OutputComponent::compute(std::size_t pin) {
        (void) pin;
        _state = getLink(1);
        return _state;
    }
}
