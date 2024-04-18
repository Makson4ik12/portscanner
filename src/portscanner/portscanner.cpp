#include "portscanner.hpp"

Scanner::Scanner(Tools& tools) {
    this->tools = tools;
}

Scanner::~Scanner() = default;

void Scanner::startScanner(std::string ip, int port_from, const int port_to) {
    ip_address = ip;

    std::cout << "Opened ports:" << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();

    if ((port_to - port_from) <= 1000) {
        scan(port_from, port_to);
    } else {
        while (port_from < port_to) {
            if ((port_from + 1000) <= port_to) {
                scan(port_from, port_from + 1000);
                port_from += 1000;
            } else {
                scan(port_from, port_to);
                break;
            }
        }
    }

    auto time = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::high_resolution_clock::now() - start_time);
    std::cout << "Scan is finished, " << time.count() / 1000 << "s" << std::endl;
}

void Scanner::scan(const int port_from, const int port_to) {
    std::map<int, int> sockets;
    int epfd = epoll_create(100);

    if (epfd == -1) 
        tools.error("epoll_create");

    for (int i = port_from; i <= port_to; i++){
        int sosk = makeSocket(epfd, i);
        
        if (sosk == -1) 
            tools.error("make socket for port" + std::to_string(i));
        else
            sockets[sosk] = i;
    }

    struct epoll_event events[port_to - port_from];
    
    int nfds = epoll_wait(epfd, events, port_to - port_from, -1);

    if (nfds == -1)
        tools.error("epoll_wait");

    for (int i = 0; i < nfds; ++i) {
        if (events[i].events & EPOLLOUT) {
            int sockfd = events[i].data.fd;
            int error = 0;
            socklen_t len = sizeof(error);

            if ((getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) != -1) && (error == 0))
                std::cout << sockets[sockfd] << std::endl;

            epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, nullptr);
            close(sockfd);
        }
    }

    for (auto& sockfd : sockets)
        close(sockfd.first);

    close(epfd);
}

int Scanner::makeSocket(int epfd, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        tools.error("too much sockets (port "  + std::to_string(port) + ")");

    int flags = fcntl(sockfd, F_GETFL, 0);

    if (flags == -1)
        tools.error("fcntl == -1");

    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        close(sockfd);
        tools.error("set non blocking mode");
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip_address.c_str(), &serverAddr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        if (errno != EINPROGRESS) {
            close(sockfd);
            return -1;
        }
    }

    struct epoll_event event;
    event.events = EPOLLOUT | EPOLLET;
    event.data.fd = sockfd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event) == -1) {
        close(sockfd);
        tools.error("epoll_ctl");
        return -1;
    }

    return sockfd;
}