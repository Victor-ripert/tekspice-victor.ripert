#include "Factory.hpp"
#include <unordered_map>
#include <functional>
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

std::unique_ptr<nts::IComponent> CompFactory::createComponent(const std::string &type) {
    static std::unordered_map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> creators;

    if (creators.empty()) {
        creators["input"] = []() { return std::make_unique<nts::InputComponent>(); };
        creators["clock"] = []() { return std::make_unique<nts::ClockComponent>(); };
        creators["output"] = []() { return std::make_unique<nts::OutputComponent>(); };
        creators["and"] = []() { return std::make_unique<nts::AndComponent>(); };
        creators["false"] = []() { return std::make_unique<nts::FalseComponent>(); };
        creators["not"] = []() { return std::make_unique<nts::NotComponent>(); };
        creators["or"] = []() { return std::make_unique<nts::OrComponent>(); };
        creators["true"] = []() { return std::make_unique<nts::TrueComponent>(); };
        creators["xor"] = []() { return std::make_unique<nts::XorComponent>(); };
    }

    auto it = creators.find(type);
    if (it != creators.end()) {
        return it->second();
    } else {
        return nullptr;
    } // probs need to add a error on other side.
}
