#include "OrComponent.hpp"

namespace nts{

    OrComponent::OrComponent(): AComponent(3) {

    };

    nts::Tristate OrComponent::compute(std::size_t pin) {
        if (pin == 1 || pin == 2) {
            return nts::Undefined;
        }
        nts::Tristate val1 = getLink(1);
        nts::Tristate val2 = getLink(2);

        if (val1 == nts::True || val2 == nts::True) {
            return nts::True;
        }

        if (val1 == nts::False && val1 == nts::False) {
            return nts::False;
        }
        return nts::Undefined;
    }
}
