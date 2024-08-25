#pragma once

#include <stdint.h>
#include <set>
#include <string>

std::set<uint64_t> get_file_block_points(const std::string& src_path, int threads_number);