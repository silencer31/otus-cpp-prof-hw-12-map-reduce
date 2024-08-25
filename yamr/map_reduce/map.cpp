#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "map.h"

void Map::run_threads(const std::set<uint64_t>& block_points)
{
    std::vector<uint64_t> offsets(block_points.begin(), block_points.end());
    
    for (std::size_t index = 0; index < offsets.size(); ++index)
    {
        uint64_t min_offset = offsets[index];
        uint64_t max_offset = index + 1 < offsets.size() ? offsets[index + 1] : -1;
        
        map_threads.emplace_back(std::thread(&Map::thread_proc, this, min_offset, max_offset, index));
    }
    
    wait_for_finished();
}

void Map::wait_for_finished()
{
    for (auto& thread : map_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Map::thread_proc(uint64_t min_offset, uint64_t max_offset, std::size_t cont_index)
{
    try
    {
        handle_file_block(min_offset, max_offset, cont_index);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Map::handle_file_block(uint64_t min_offset, uint64_t max_offset, std::size_t cont_index)
{
    MapFunctor functor;

    //assert(aMaxOffset == 1 || max_offset >= min_offset);
    std::ifstream src_stream(src_file_path);
    src_stream.seekg(min_offset);
    std::string file_line;
    
    MapContainer& container = map_containers[cont_index];

    while (std::getline(src_stream, file_line) && (max_offset == -1 || static_cast<uint64_t>(src_stream.tellg()) <= max_offset))
    {
        if (file_line.length() > 0 && file_line[file_line.length() - 1] == '\r') {
            file_line = file_line.substr(0, file_line.length() - 1);
        }

        functor.add_line(file_line);
    }

    for (const std::string& line : functor()) {
        container.insert_line(line);
    }
}
