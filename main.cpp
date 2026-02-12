#include "Circuit.hpp"
#include "FileReader.hpp"
#include "UserInput.hpp"



int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file.nts>\n";
        return 84;
    }
    Circuit circuit;
    std::cout << "made here" << std::endl;
    FileReader reader(circuit, argv[1]);
    UserInput input(circuit);

    input.runInputs();
}
