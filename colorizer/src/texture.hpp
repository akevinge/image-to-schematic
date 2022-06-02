#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "img.hpp"

class texture {
   private:
    img& image;

   public:
    std::vector<pixel> pixels;
    const std::string name;
    texture(const std::string& n, img& l);
    rgba calc_best_color(int repetitions);  // some knock off k-means algo lol
};

#endif