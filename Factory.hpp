#pragma once

#include "IComponent.hpp"
#include <memory>

class CompFactory {
    public:
    std::unique_ptr<nts::IComponent> createComponent(const std::string &type);

};