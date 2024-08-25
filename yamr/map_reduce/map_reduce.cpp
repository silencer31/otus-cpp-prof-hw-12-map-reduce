#include "map_reduce.h"

MapReduce::MapReduce(const std::string& file_path,
    int mtn, int rtn,
    std::set<uint64_t>&& bp)
    : src_file_path(file_path)
    , map_threads_number(mtn)
    , reduce_threads_number(rtn)
    , block_points(bp)
    , map_obj(src_file_path, map_threads_number, map_containers)
    , shuffle_obj(map_threads_number, reduce_threads_number, map_containers, shuffle_containers)
    , reduce_obj(reduce_threads_number, shuffle_containers)
{
    map_containers.resize(map_threads_number);
    shuffle_containers.resize(reduce_threads_number);
}

void MapReduce::start()
{
    map_obj.Run(block_points);
    shuffle_obj.Run();
    reduce_obj.Run();
}