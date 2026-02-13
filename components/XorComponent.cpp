#include "include/components/XorComponent.hpp"

namespace nts{

    XorComponent::XorComponent(): AComponent(3, XOrComp){

    };

    nts::Tristate XorComponent::compute(std::size_t pin) {
        if (pin == 1 || pin == 2) {
            return nts::Undefined;
        }
        nts::Tristate val1 = getLink(1);
        nts::Tristate val2 = getLink(2);

        if (val1 == nts::Undefined || val2 == nts::Undefined) {
            return nts::Undefined;
        }

        if (val1 != val2) {
            return nts::True;
        }
        return nts::False;
    }
}
