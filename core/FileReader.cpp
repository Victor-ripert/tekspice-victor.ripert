#include "include/core/FileReader.hpp"
#include "include/core/NanoTekSpiceExceptions.hpp"

FileReader::FileReader(Circuit &circuit, std::string FilePath)
    : _file(FilePath), _circuit(circuit), _section(none) {
    if (!_file.is_open())
        throw nts::NanoExecption("Couldn't open the file");
}

void FileReader::trimComments(std::string &line) {
    size_t index = line.find('#');
    if (index != std::string::npos)
        line = line.substr(0, index);

    size_t start = line.find_first_not_of(" \t");
    size_t end   = line.find_last_not_of(" \t");
    line = (start == std::string::npos) ? "" : line.substr(start, end - start + 1);
}

bool FileReader::updateSection(std::string line) {
    if (line == ".chipsets:" || line == ".chipsets") {
        _section = chipset;
        return true;
    }
    if (line == ".links:" || line == ".links") {
        _section = links;
        return true;
    }
    return false;
}


void FileReader::addChipset(std::string &line) {
    size_t typePos = line.find_first_of(" \t");
    if (typePos == std::string::npos)
        throw nts::NanoExecption("addChipset(): component type not found");

    std::string type = line.substr(0, typePos);

    size_t namePos = line.find_first_not_of(" \t", typePos);
    if (namePos == std::string::npos)
        throw nts::NanoExecption("addChipset(): component name not found");

    size_t nameEnd = line.find_last_not_of(" \t");
    std::string name = line.substr(namePos, nameEnd - namePos + 1);

    _circuit.addComponent(name, type);
}

NamePin FileReader::getNamePin(std::string &linePart) {
    size_t pos = linePart.find(':');
    if (pos == std::string::npos)
        throw nts::NanoExecption("getNamePin(): missing ':' in link part");

    NamePin np;
    np.name = linePart.substr(0, pos);

    std::string pin = linePart.substr(pos + 1);
    try {
        np.pin = std::stoul(pin);
    } catch (...) {
        throw nts::NanoExecption(("getNamePin(): invalid pin number: " + pin).c_str());
    }
    return np;
}

void FileReader::addLink(std::string &line) {
    size_t link1Pos = line.find_first_of(" \t");
    if (link1Pos == std::string::npos)
        throw nts::NanoExecption("addLink(): couldn't find the first link");

    std::string link1 = line.substr(0, link1Pos);

    size_t link2Pos = line.find_first_not_of(" \t", link1Pos);
    if (link2Pos == std::string::npos)
        throw nts::NanoExecption("addLink(): couldn't find the second link");

    std::string link2 = line.substr(link2Pos);

    _circuit.linkComponents(getNamePin(link1), getNamePin(link2));
}

void FileReader::filterLine(std::string &line) {
    if (_section == none)
        throw nts::NanoExecption("filterLine(): content found outside of a section");
    if (_section == chipset)
        addChipset(line);
    else if (_section == links)
        addLink(line);
}

void FileReader::parseFile() {
    std::string line;
    while (getline(_file, line)) {
        trimComments(line);
        if (line.find_first_not_of(" \t") == std::string::npos)
            continue;
        if (updateSection(line))
            continue;
        filterLine(line);
    }
}