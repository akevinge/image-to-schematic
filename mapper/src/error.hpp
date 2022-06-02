#ifndef MAPPER_ERROR_HPP
#define MAPPER_ERROR_HPP

#include <iostream>
#include <string>

inline void print_error(const std::string& msg) {
    std::cerr << "[mapper error]: " << msg << std::endl;
}

#endif