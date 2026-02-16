#pragma once

#include <iostream>


namespace nts
{
    enum Tristate {
        Undefined = (-true),
        True = true,
        False = false
    };

    enum CompType {
        InputComp,
        ClockComp,
        OutputComp,
        AndComp,
        FalseComp,
        NotComp,
        OrComp,
        TrueComp,
        XOrComp,
        UnkownComp,
        NorComp,
        NandComp,
        Comp4001,
        Comp4071,
        Comp4011
        // NEED TO ADD THE REST
    };

    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        // virtual void simulate(std::size_t tick) = 0;
        virtual nts::Tristate compute(std::size_t pin) = 0;
        virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
        virtual nts::Tristate getLink(std::size_t pin) = 0;
        virtual nts::CompType getType() = 0;
        virtual void setType(nts::CompType type) = 0;
        virtual void setTristate(nts::Tristate) = 0;
        virtual nts::Tristate getTristate() = 0;
        virtual void setOneWayLink(IComponent& component, std::size_t pin, std::size_t otherPin) = 0;
    };
};

