#include "include/components/XorComponent.hpp"

namespace nts{

    XorComponent::XorComponent(): AComponent(3, XOrComp){

    };

    nts::Tristate XorComponent::compute(std::size_t pin) {
        if (_computing)
            return _state;
        _computing = true;
        if (pin == 1 || pin == 2) {
            _computing = false;
            return getLink(pin);
        }
        nts::Tristate val1 = getLink(1);
        nts::Tristate val2 = getLink(2);
        if (val1 == nts::Undefined || val2 == nts::Undefined)
            _state = nts::Undefined;
        else if (val1 != val2)
            _state = nts::True;
        else
            _state = nts::False;
        _computing = false;
        return _state;
    }

}
