#include "portscanner.hpp"

int main(int argc, char* argv[]) {
    Tools tools;
    
    if (argc != 4) {
        std::cout << "Usage: scanner <IPv4> <port_from> <port_to>" << std::endl;
        exit(-1);
    }

    if(!tools.validateIP(argv[1]))
        tools.error("IPv4 is not correct");

    if (!tools.validatePorts(argv[2], argv[3]))
        tools.error("ports are not correct");

    Scanner scanner(tools);
    scanner.startScanner(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
}