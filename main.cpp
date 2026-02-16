#include "include/core/Circuit.hpp"
#include "include/core/FileReader.hpp"
#include "include/core/UserInput.hpp"
#include "include/core/NanoTekSpiceExceptions.hpp"



int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file.nts>\n";
        return 84;
    }
    try {
        Circuit circuit;
        // std::cout << argv[1] << std::endl;
        FileReader reader(circuit, argv[1]);
        reader.parseFile();
        UserInput input(circuit);
        input.runInputs();
    } catch(nts::NanoExecption &e) {
        std::cerr << e.what() << std::endl;
    }

}
