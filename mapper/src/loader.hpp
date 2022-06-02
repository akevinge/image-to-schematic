#ifndef LOADER_HPP
#define LOADER_HPP

#include <optional>
#include <vector>

#include "block.hpp"
#include "img.hpp"

std::optional<img> load_img(const std::string& file_path);

std::optional<std::vector<block>> load_block_colors(const std::string& blockfolder, const std::string& colorfile);

#endif