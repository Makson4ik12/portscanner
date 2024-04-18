#pragma once

#ifndef PORTSCANNER_H
#define PORTSCANNER_H

#include "tools.hpp"

class Scanner {
    public:
    Scanner(Tools& tools);
    ~Scanner();

    void startScanner(const std::string ip, int port_from, const int port_to);
    int makeSocket(int epfd, int port);

    private:
    std::string ip_address;
    void scan(const int port_from, const int port_to);
    Tools tools;
};

#endif