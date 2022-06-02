#include "texture.hpp"

#include <math.h>

#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> distr(0, 15);

int px_rand() {
    return distr(gen);
}

int color_dist(rgba x, rgba y) {
    return std::pow(x.r - y.r, 2) + std::pow(x.g - y.g, 2) + std::pow(x.b - y.b, 2);
}

texture::texture(const std::string& n, img& l) : name(n), pixels(l.extract_pixels()), image(l) {}

rgba texture::calc_best_color(int repetitions) {
    int least_variance{};
    rgba best_color;
    for (int k{}; k < repetitions; k++) {
        // pretend the pixel at c has the best color
        int c[2] = {px_rand(), px_rand()};
        int px_idx = c[0] * image.h + c[1];
        const pixel& mean_px = pixels.at(px_idx);

        int variance{};
        for (int x{}; x < image.w; x++) {
            for (int y{}; y < image.h; y++) {
                const pixel& observed_px = pixels.at(x * image.h + y);
                variance += color_dist(mean_px.color, observed_px.color);
            }
        }

        if (k == 0) {
            least_variance = variance;
            best_color = mean_px.color;
            continue;
        }

        if (variance < least_variance) {
            least_variance = variance;
            best_color = mean_px.color;
        }
    }

    return best_color;
}