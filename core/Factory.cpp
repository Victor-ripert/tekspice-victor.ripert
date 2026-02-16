#include "include/core/Factory.hpp"
#include <unordered_map>
#include <functional>
#include "include/components/AComponent.hpp"
#include "include/components/AndComponent.hpp"
#include "include/components/ClockComponent.hpp"
#include "include/components/FalseComponent.hpp"
#include "include/components/InputComponent.hpp"
#include "include/components/NotComponent.hpp"
#include "include/components/OrComponent.hpp"
#include "include/components/OutputComponent.hpp"
#include "include/components/TrueComponent.hpp"
#include "include/components/XorComponent.hpp"
#include "include/components/NorComponent.hpp"
#include "include/components/NandComponent.hpp"
#include "include/components/Component4071.hpp"
#include "include/components/Component4001.hpp"
#include "include/components/Component4011.hpp"
#include "include/core/NanoTekSpiceExceptions.hpp"

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
        creators["nor"] = []() { return std::make_unique<nts::NorComponent>(); };
        creators["nand"] = []() { return std::make_unique<nts::NandComponent>(); };
        creators["4071"] = []() { return std::make_unique<nts::Component4071>(); };
        creators["4001"] = []() { return std::make_unique<nts::Component4001>(); };
        creators["4011"] = []() { return std::make_unique<nts::Component4011>(); };
    }

    auto it = creators.find(type);
    if (it != creators.end()) {
        return it->second();
    } else {
        throw nts::NanoExecption((type + " is not a supported component type").c_str());
        return nullptr;
    } // probs need to add a error on other side.
}
