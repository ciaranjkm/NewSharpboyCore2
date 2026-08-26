#pragma once

#include <common.h>
#include <filesystem>
#include <fstream>
#include <span>

bool load_file(const std::filesystem::path& path, std::span<u8> buffer);