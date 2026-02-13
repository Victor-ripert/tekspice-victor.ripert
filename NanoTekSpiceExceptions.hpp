/*
** EPITECH PROJECT, 2026
** OOP module
** File description:
** Nano Tek Spice
*/

#include <exception>
#include <string>

#ifndef NANOTEKSPICEEXECEPTIONS_HPP
    #define NANOTEKSPICEEXECEPTIONS_HPP

namespace nts {
    class NanoExecption : public std::exception {
        private:
            std::string _msg;

        public:
            NanoExecption(const char *msg);
            const char *what() const noexcept override;
    };
}

#endif /* NANOTEKSPICEEXECEPTIONS_HPP */