#include "img.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include <filesystem>
#include <fstream>
#include <optional>
#include <string>

#include "error.hpp"
#include "json.hpp"
#include "stb_image.h"
#include "texture.hpp"

using json = nlohmann::json;

std::optional<img> load_img(const std::string& file_path) {
    try {
        img loader(file_path);
        return loader;
    } catch (const std::runtime_error& e) {
        print_error("failed to load " + file_path);
        return std::nullopt;
    }
}

std::string get_name(const std::string& path) {
    return path.substr(path.rfind("/") + 1, path.length() - path.rfind("/") - 5);
}

struct args {
    std::string texture_dir;
    std::string out_file;
    int precision;
};

std::optional<args> parse_args(char* argv[]) {
    try {
        return args{argv[1], argv[2], std::stoi(argv[3])};
    } catch (const std::exception& e) {
        return std::nullopt;
    }
}

int main(int argc, char* argv[]) {
    auto args = parse_args(argv);

    if (!args.has_value() || args->precision == 0) {
        print_error("invalid arguments");
        return 1;
    }

    if (!(std::filesystem::exists(args->texture_dir))) {
        print_error("could not find " + args->texture_dir);
        return 1;
    }

    try {
        json j;
        for (auto file : std::filesystem::directory_iterator(args->texture_dir)) {
            std::string file_path = file.path();
            std::string name = get_name(file_path);

            auto img = load_img(file_path);
            if (img.has_value()) {
                texture t(name, *img);
                auto c = t.calc_best_color(args->precision);
                j[t.name] = c.to_array();
            }
        }

        std::ofstream out_file(args->out_file);
        out_file << j.dump(2);
        out_file.close();
        std::cout << "successfully generated colors at " << args->out_file << std::endl;
    } catch (const std::exception& e) {
        print_error(std::string(e.what()));
        return 1;
    }

    return 0;
}
