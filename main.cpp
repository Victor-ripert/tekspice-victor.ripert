#include "IComponent.hpp"
#include <memory>

#include "AComponent.hpp"
#include "AndComponent.hpp"
#include "ClockComponent.hpp"
#include "FalseComponent.hpp"
#include "InputComponent.hpp"
#include "NotComponent.hpp"
#include "OrComponent.hpp"
#include "OutputComponent.hpp"
#include "TrueComponent.hpp"
#include "XorComponent.hpp"

std::ostream &operator<<(std::ostream &s, nts::Tristate v)
{
    switch (v) {
    case nts::Undefined:
        s << "U";
        break;
    case nts::True:
        s << "1";
        break;
    case nts::False:
        s << "0";
        break;
    default:
        break;
    }
    return s;
}

int main(void)
{
    std::unique_ptr<nts::IComponent> gate = std::make_unique<nts::AndComponent>();
    std::unique_ptr<nts::IComponent> input1 = std::make_unique<nts::FalseComponent>();
    std::unique_ptr<nts::IComponent> input2 = std::make_unique<nts::TrueComponent>();
    std::unique_ptr<nts::IComponent> inverter = std::make_unique<nts::NotComponent>();

    gate->setLink(1, *input1, 1);
    gate->setLink(2, *input2, 1);
    inverter->setLink(1, *gate, 3);

    std::cout << "!(" << input1->compute(1) << " && " << input2->compute(1) << ") -> "
              << inverter->compute(2) << std::endl;
}
