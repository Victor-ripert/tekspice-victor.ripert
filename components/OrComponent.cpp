#include "include/components/OrComponent.hpp"

namespace nts{

    OrComponent::OrComponent(): AComponent(3, nts::OrComp) {

    };

    nts::Tristate OrComponent::compute(std::size_t pin) {
        if (_computing)
            return _state;
        _computing = true;
        if (pin == 1 || pin == 2) {
            _computing = false;
            return getLink(pin);
        }
        nts::Tristate val1 = getLink(1);
        nts::Tristate val2 = getLink(2);
        if (val1 == nts::True || val2 == nts::True)
            _state = nts::True;
        else if (val1 == nts::False && val2 == nts::False)
            _state = nts::False;
        else
            _state = nts::Undefined;
        _computing = false;
        return _state;
    }

}
