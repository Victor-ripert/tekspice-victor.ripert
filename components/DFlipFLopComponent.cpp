/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** DFlipFlopComponent
*/


#include <memory>

#include "include/components/OrComponent.hpp"
#include "include/components/NorComponent.hpp"
#include "include/components/NotComponent.hpp"
#include "include/components/AndComponent.hpp"
#include "include/components/DFlipFlopComponent.hpp"

namespace nts {
    const std::set<int> DFlipFlopComponent::_input_pins = {1, 2, 3, 4};

/*
D FLip Flop's Pins table :
pin1 -> Data (the boelan you want to save)
pin2 -> Clock (special pin for the clock that save or flush the data)
pin3 -> SET' / PRE' (set pin5 to 1 and pin6 to 0, asynchrounously without using the clock)
pin4 -> RESET' / CLEAR' (set pin5 to 0 and pin6 to 1, idem)
pin5 -> Output (value of the saved data)
pin6 -> Output' / Inversed Output (the inverse of the saved data)

/!\ if Pin3 and Pin4 are used as the same time, both pin5 and 6 will return 1 /!\
Also: Pin3 and Pin3 are "active" when their value are low (0 / false)
*/

    DFlipFlopComponent::DFlipFlopComponent() : AComponent(6, nts::DFlipFlopComp) {
        _components = std::vector<std::unique_ptr<IComponent>>(13);
        // 2 And Gates
        _components[0] = std::make_unique<AndComponent>(); // and1
        _components[1] = std::make_unique<AndComponent>(); // and2

        // 2 Or Gates
        _components[2] = std::make_unique<OrComponent>(); // or1
        _components[3] = std::make_unique<OrComponent>(); // or2

        // 4 Nor Gates
        _components[4] = std::make_unique<NorComponent>(); // nor1
        _components[5] = std::make_unique<NorComponent>(); // nor2
        _components[6] = std::make_unique<NorComponent>(); // nor3
        _components[7] = std::make_unique<NorComponent>(); // nor4

        // Five Not Gates
        _components[8] = std::make_unique<NotComponent>(); // not1
        _components[9] = std::make_unique<NotComponent>(); // not2
        _components[10] = std::make_unique<NotComponent>(); // not3
        _components[11] = std::make_unique<NotComponent>(); // not4
        _components[12] = std::make_unique<NotComponent>(); // not5


        // Not1 = _components[8] (pin1 (data))
        setOneWayLink(*_components[8], 1, 1);
        // And1 = _components[0] (Not1(pin2), pin2 (Clock))
        _components[0]->setLink(1, *_components[8], 2); // Not1(pin2)
        setOneWayLink(*_components[0], 2, 2);
        // And2 = _components[1] (pin1 (data), pin2 (Clock))
        setOneWayLink(*_components[1], 1, 1);
        setOneWayLink(*_components[1], 2, 2);
        // Nor1 = _components[4] (And1(pin3), Nor2(pin3))
        _components[4]->setLink(1, *_components[0], 3); // And1(pin3)
        _components[4]->setLink(2, *_components[5], 3); // Nor2(pin3)
        // Nor2 = _components[5] (And2(pin3), Nor1(pin3))
        _components[5]->setLink(1, *_components[1], 3); // And2(pin3)
        _components[5]->setLink(2, *_components[4], 3); // Nor1(pin3)
        // Not2 = _components[9] (Nor1(pin3))
        _components[9]->setLink(1, *_components[4], 3); // Nor1(pin3)
        // Not3 = _components[10] (pin3 (Set/Pre))
        setOneWayLink(*_components[10], 1, 3);
        // Not4 = _components[11] (pin4 (Reset/Clear))
        setOneWayLink(*_components[11], 1, 4);
        // Not5 = _components[12] (Nor2(pin3))
        _components[12]->setLink(1, *_components[5], 3); // Nor2(pin3)
        // Nor3 = _components[6] (Not2(pin2), Not4(pin2))
        _components[6]->setLink(1, *_components[9], 2);
        _components[6]->setLink(2, *_components[11], 2);
        // Nor4 = _components[7] (Not3(pin2), Not5(pin2))
        _components[7]->setLink(1, *_components[10], 2);
        _components[7]->setLink(2, *_components[12], 2);
        // Or1 = _components[2] (Nor3(pin3), Not3(pin2))
        _components[2]->setLink(1, *_components[6], 3);
        _components[2]->setLink(2, *_components[10], 2);
        // Or2 = _components[3] (Nor4(pin3), Not4(pin2))
        _components[3]->setLink(1, *_components[7], 3);
        _components[3]->setLink(2, *_components[11], 2);

        // Contected to the output Or1 -> pin5 & Or2 -> pin6
        setOneWayLink(*_components[2], 3, 5);
        setOneWayLink(*_components[3], 3, 6);
    }

    nts::Tristate DFlipFlopComponent::compute(std::size_t pin) {
        if (_input_pins.find(pin) != _input_pins.end())
            return getLink(pin); // Inputs
        switch (pin) { // Outputs
            case 5:
                return this->_components[10]->compute(2); // Output
            case 6:
                return this->_components[3]->compute(3); // Output' (inversed)
            default:
                return nts::Tristate::Undefined;
        }
    }
}