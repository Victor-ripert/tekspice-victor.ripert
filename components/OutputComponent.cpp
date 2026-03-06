#include "include/components/OutputComponent.hpp"

namespace nts{

    OutputComponent::OutputComponent(): AComponent(1, nts::OutputComp) {

    };

    nts::Tristate OutputComponent::compute(std::size_t pin) {
        (void) pin;
        if (_computing)
            return _state;
        _computing = true;
        _state = getLink(1);
        _computing = false;
        return _state;
    }

}
