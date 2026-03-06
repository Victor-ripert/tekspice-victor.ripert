#include "include/components/NotComponent.hpp"

namespace nts{

    NotComponent::NotComponent(): AComponent(2, nts::NotComp){

    };
    nts::Tristate NotComponent::compute(std::size_t pin) {
        if (_computing)
            return _state;
        _computing = true;
        if (pin == 1) {
            _computing = false;
            return getLink(pin);
        }
        nts::Tristate val1 = getLink(1);
        if (val1 == nts::False)
            _state = nts::True;
        else if (val1 == nts::True)
            _state = nts::False;
        else
            _state = val1;
        _computing = false;
        return _state;
    }
}
