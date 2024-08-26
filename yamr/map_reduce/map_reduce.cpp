#include "map_reduce.h"

#include <iostream>

MapReduce::MapReduce(const std::string& src_file_path,
    unsigned int map_threads_number, unsigned int reduce_threads_number,
    std::set<uint64_t>&& bp) 
    : block_points(bp)
    , map_obj(src_file_path, map_containers)
    , shuffle_obj(map_threads_number, reduce_threads_number, map_containers, shuffle_containers)
    , reduce_obj(reduce_threads_number, shuffle_containers)
{
    map_containers.resize(map_threads_number);
    shuffle_containers.resize(reduce_threads_number);
}

void MapReduce::start()
{
    map_obj.run_threads(block_points);
    shuffle_obj.run_threads();
    reduce_obj.run_threads();

    std::cout << "\nMapReduce completed" << std::endl;
}