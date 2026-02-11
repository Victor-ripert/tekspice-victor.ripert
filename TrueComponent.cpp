#include "TrueComponent.hpp"

namespace nts{

    TrueComponent::TrueComponent():AComponent(1, TrueComp, nts::True){

    }
    nts::Tristate TrueComponent::compute(std::size_t pin) {
        (void)pin;
        return nts::True;
    };
}
