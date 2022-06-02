#include "loader.hpp"

#include <array>
#include <fstream>

#include "block.hpp"
#include "error.hpp"
#include "filesystem"
#include "json.hpp"

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

std::optional<json> load_colors(const std::string& path) {
    try {
        std::ifstream file(path);
        json j;
        if (file.is_open() && file.good()) {
            file >> j;
        }
        file.close();

        return j;
    } catch (const std::ios_base::failure& e) {
        print_error("failed to load " + path);
        return std::nullopt;
    }
}

std::string get_name(const std::string& path) {
    return path.substr(path.rfind("/") + 1, path.length() - path.rfind("/") - 5);
}

std::optional<std::vector<block>> load_block_colors(const std::string& blockfolder, const std::string& colorfile) {
    const auto colors_opt = load_colors(colorfile);
    if (!colors_opt.has_value()) return std::nullopt;
    auto colors = colors_opt.value();

    try {
        std::vector<block> blocks;
        for (const auto& file : std::filesystem::directory_iterator(blockfolder)) {
            const std::string& name = get_name(file.path());

            blocks.push_back(block(file.path(), name, (std::array<int, 4>)colors[name]));
        }
        // super hacky way to trim textures, implementing a copy ctor on block.image is really hard
        // @TODO: consider making image.data a shared_ptr
        for (auto& b : blocks) {
            if (b.image.w != 16 || b.image.h != 16) {
                trim_block_16x16(b);
            }
        }
        return blocks;
    } catch (const std::runtime_error& e) {
        return std::nullopt;
    }
}
