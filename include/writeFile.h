#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <filesystem>

int writeFileAsBytes(const std::filesystem::path& filename, const std::vector<uint8_t>& buffer);