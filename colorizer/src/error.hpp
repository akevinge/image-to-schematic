#ifndef COLORIZER_ERROR_HPP
#define COLORIZER_ERROR_HPP

#include <iostream>
#include <string>

void print_error(const std::string& msg) {
    std::cerr << "[colorizer error]: " << msg << std::endl;
}

#endif