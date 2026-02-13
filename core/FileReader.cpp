#include "include/core/FileReader.hpp"
#include "include/core/NanoTekSpiceExceptions.hpp"

FileReader::FileReader(Circuit &circuit , std::string FilePath) : _file(FilePath), _circuit(circuit), _section(none) {
    if (!_file.is_open()) {
        throw nts::NanoExecption("Couldn't open the file");
    }
}

void FileReader::trimComments(std::string &line) {
    size_t index = line.find('#');
    if (index != std::string::npos) {
        line = line.substr(0, index);
    }
}

bool FileReader::updateSection(std::string line) {
    if (line == ".chipsets:") {
        _section = chipset;
        return true;
    }
    if  (line == ".links:") {
        _section = links;
        return true;
    }
    return false;
};

void FileReader::addChipset(std::string &line) {
    size_t typePos = line.find_first_of(" \t");
    if (typePos == std::string::npos) {
        throw nts::NanoExecption("addChipset: type not found");
        return;
    }
    std::string type = line.substr(0, typePos);
    size_t namePos = line.find_first_not_of(" \t", typePos);

    if (namePos == std::string::npos) {
        throw nts::NanoExecption("addChipset: name not found");
        return;
    }
    std::string name = line.substr(namePos);
    _circuit.addComponent(name, type);
};


NamePin FileReader::getNamePin(std::string &linePart) {
    size_t pos = linePart.find(':');
    NamePin np;
    if (pos == std::string::npos) {
    return np;
    }
    np.name = linePart.substr(0, pos);
    std::string pin = linePart.substr(pos + 1);
    np.pin = std::stoul(pin);
    return np;
}

//needs work
void FileReader::addLink(std::string &line) {
    size_t link1Pos = line.find_first_of(" \t");
    if (link1Pos == std::string::npos) {
        throw nts::NanoExecption("addLink(): couldn't find the first link");
        return;
    }
    std::string link1 = line.substr(0, link1Pos);
    size_t link2Pos = line.find_first_not_of(" \t", link1Pos);

    if (link2Pos == std::string::npos) {
        throw nts::NanoExecption("addLink(): couldn't find the second link");
        return;
    }
    std::string link2 = line.substr(link2Pos);
    _circuit.linkComponents(getNamePin(link1), getNamePin(link2));
}

void FileReader::filterLine(std::string &line) {
    if (_section == chipset) {
        addChipset(line);
        return;
    }
    if (_section == links) {
        addLink(line);
        return;
    }
    return;
};

void FileReader::parseFile() {
    std::string line;
    while (getline (_file, line)) {
        trimComments(line);
        if (line.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }
        if (updateSection(line)) {
            continue;
        }
        filterLine(line);
      }
};