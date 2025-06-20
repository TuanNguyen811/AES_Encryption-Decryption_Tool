#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <filesystem>

std::vector<uint8_t> readFileAsBytes(const std::filesystem::path& filename);