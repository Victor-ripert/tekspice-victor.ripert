/*
** EPITECH PROJECT, 2026
** OOP module
** File description:
** Nano Tek Spice
*/

#include "NanoTekSpiceExceptions.hpp"
#include <string>

nts::NanoExecption::NanoExecption(const char *msg) {
    this->_msg = msg;
}

const char *nts::NanoExecption::what() const noexcept{
    // std::string msg("Error : ");
    // msg.append(this->_msg);
    // return msg.data();
    return _msg.c_str();
}