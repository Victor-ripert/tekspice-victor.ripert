#pragma once

#include "Circuit.hpp"
#include <iostream>
#include <fstream>
#include <string>

enum FileSection {
    chipset,
    links,
    none
};

struct NamePin {
    std::string name;
    size_t pin;
};

class Circuit;

class FileReader
{
private:
    std::ifstream _file;
    Circuit &_circuit;
    FileSection _section;
    NamePin getNamePin(std::string &linePart);
    void trimComments(std::string &line);
    bool updateSection(std::string line);
    void filterLine(std::string &line);
    void addChipset(std::string &line);
    void addLink(std::string &line);
public:
    FileReader(Circuit &circuit, std::string FilePath);
    void parseFile();
    ~FileReader() = default;
};
