#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdlib.h>

#include <array>
#include <cstring>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "stb_image.h"

struct rgba {
    u_char r;
    u_char g;
    u_char b;
    u_char a;
    rgba() : r(0), g(0), b(0), a(0) {}
    rgba(u_char r, u_char g, u_char b, u_char a) : r(r), g(g), b(b), a(a) {}
    rgba(std::array<int, 4> ar) : r(ar[0]), g(ar[1]), b(ar[2]), a(ar[3]) {}

    std::string to_string() {
        return std::to_string((int)r) + "," + std::to_string((int)g) + "," + std::to_string((int)b) + "," + std::to_string((int)a);
    }

    std::array<u_char, 4> to_array() {
        return std::array<u_char, 4>{r, g, b, a};
    }
};

struct pixel {
    int x;
    int y;
    rgba color;

    pixel(int x, int y, const rgba& c) : x(x), y(y), color(c) {}
};

struct delete_img_data {
    void operator()(u_char* d) const {
        if (d != NULL && d != nullptr) {
            stbi_image_free(d);
        }
    }
};

typedef std::unique_ptr<u_char, delete_img_data> img_data_ptr;

class img {
    int m_w = 0;
    int m_h = 0;
    int m_comp = 0;  // # of 1-byte components for a pixel

   public:
    const int& w = m_w;
    const int& h = m_h;
    const int& comp = m_comp;
    img_data_ptr data;

    img(int w, int h, int comp, u_char* d) : m_w(w), m_h(h), m_comp(comp), data(img_data_ptr(d)) {}
    img(const std::string& file_path) {
        int req_chan = 3;
        int w, h, n;
        u_char* img_data = stbi_load(file_path.c_str(), &w, &h, &n, req_chan);

        if (img_data == NULL || w == 0 || h == 0) {
            throw std::runtime_error("unable to load " + file_path + ", possibly corrupted file");
        }

        if (n < 3) {
            throw std::runtime_error("unable to load correct amount of channels, expected 3 or more channels, got: " + std::to_string(n));
        }

        m_w = w;
        m_h = h;
        m_comp = req_chan;

        data = img_data_ptr{img_data};
    }
    img(img&& other) : m_w(other.w), m_h(other.h), m_comp(other.comp), data(std::move(other.data)) {}

    void change_w(int w) { m_w = w; }
    void change_h(int h) { m_h = h; }

    std::vector<pixel> extract_pixels() {
        std::vector<pixel> pixels;
        for (int x{}; x < w; x++) {
            for (int y{}; y < h; y++) {
                u_char* p = data.get() + (x + y * w) * comp;
                rgba c = {
                    p[0],
                    p[1],
                    p[2],
                    comp >= 4 ? p[3] : static_cast<u_char>(255),
                };
                pixels.push_back(pixel(x, y, c));
            }
        }
        return pixels;
    }

    void insert_img_at(const img& append_img, int x, int y) {
        if (append_img.comp != comp) {
            throw std::runtime_error("image objects have mismatched number of components");
        }
        if (x + append_img.w > w || y + append_img.h > h) {
            throw std::runtime_error("attempting to write outside of image bounds");
        }

        for (int row{}; row < append_img.h; row++) {
            int y_skip = (y + row) * w;
            memcpy(data.get() + comp * (x + y_skip), append_img.data.get() + append_img.w * row * comp, append_img.w * comp);
        }
    }
};

#endif
