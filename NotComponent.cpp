#include "NotComponent.hpp"

namespace nts{

    NotComponent::NotComponent(): AComponent(2){

    };
    nts::Tristate NotComponent::compute(std::size_t pin) {
        if (pin == 1) {
            return nts::Undefined;
        }
        nts::Tristate val1 = getLink(1);
        if (val1 == nts::False)
            return nts::True;
        if (val1 == nts::True)
            return nts::False;
        return val1;
    }
}
