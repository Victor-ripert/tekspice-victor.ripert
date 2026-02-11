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

class FileReader
{
private:
    std::ifstream _file;
    Circuit &_circuit;
    FileSection _section;
    void trimComments(std::string &line);
    bool updateSection(std::string line);
    void filterLine(std::string &line);
    void addChipset(std::string &line);
    void addLink(std::string &line);
public:
    FileReader(Circuit &circuit, std::string FilePath);
    void parseFile();
    ~FileReader();
};
