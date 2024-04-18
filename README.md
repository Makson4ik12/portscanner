# Port scanner

Utility for searching open ports on a remote server

## Requirements

CMake 3.22+
g++

## Target OS

Linux

## Build

mkdir build
cd build
cmake ../../portscanner
cmake --build ../build

## Usage
```
scanner <target_ip> <port_range_start> <port_range_end>
example: scanner 192.168.0.12 100 1000 - scanning 100-1000 ports of 192.168.0.12
```