#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <optional>
#include <string>

#include "img.hpp"

class block {
   public:
    std::string name;
    rgba color;
    img image;

    block(const std::string& filename, const std::string& name, const rgba& color) : image(img(filename)), name(name), color(color) {}
    bool operator==(const std::string& b_name) {
        return b_name == name;
    }
};

// some textures have dimensions exceeding 16x16 pixels, will return true if already 16x16
bool trim_block_16x16(block& b);

#endif