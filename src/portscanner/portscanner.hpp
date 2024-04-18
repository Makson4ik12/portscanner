#pragma once

#ifndef PORTSCANNER_H
#define PORTSCANNER_H

#include "tools.hpp"

class Scanner {
    public:
    Scanner(Tools& tools);
    ~Scanner();

    void startScanner(const std::string ip, int port_from, const int port_to);

    private:
    std::string ip_address;
    Tools tools;
    void scan(const int port_from, const int port_to);
    int makeSocket(int epfd, int port);
};

#endif