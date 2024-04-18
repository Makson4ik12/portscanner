#include "tools.hpp"

Tools::Tools() = default;

Tools::~Tools() = default;

int Tools::validateIP(std::string ip_string) {
    size_t pos_start = 0, pos_end;
    std::string token;
    std::vector<std::string> ip_parts;

    while ((pos_end = ip_string.find(".", pos_start)) != std::string::npos) {
        token = ip_string.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        ip_parts.push_back (token);
    }

    ip_parts.push_back (ip_string.substr(pos_start));

    if (ip_parts.size() != 4) return 0;

    for (std::string& part : ip_parts) {
        if (part.size() == 0) return 0;

        int value = std::stoi(part);
        if ((value < 0) || (value > 255)) return 0;
    }

    return 1;
}

int Tools::validatePorts(std::string port_from, std::string port_to) {
    int port_0 = 0, port_1 = 0;

    try
    {
        port_0 = std::stoi(port_from);
        port_1 = std::stoi(port_to);
    }
    catch (std::invalid_argument ex)
    {
        return 0;
    }
    catch (std::out_of_range ex)
    {
        return 0;
    }

    if ((port_0 < 0) || (port_0 > 65535) || (port_1 < 0) || (port_1 > 65535) || (port_0 > port_1)) return 0;

    return 1;
}

void Tools::error(std::string message) {
    std::cerr << "Error: " << message << std::endl;
    std::exit(-1);
}