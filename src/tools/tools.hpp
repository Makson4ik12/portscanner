#pragma once

#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <chrono>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

class Tools {
    public:
    Tools();
    ~Tools();

    int validateIP(std::string ip_string);
    int validatePorts(std::string port_from, std::string port_to);
    void error(std::string message);
};

#endif