#pragma once

#include "map.h"
#include "reduce.h"
#include "../shuffle/shuffle.h"

#include <stdint.h>

class MapReduce
{
public:
    MapReduce(const std::string& file_path,
        int mtn, int rtn,
        std::set<uint64_t>&& bp);

    void start();

private:
    const std::string src_file_path;
    const int map_threads_number;
    const int reduce_threads_number;
    const std::set<uint64_t> block_points;
    
    std::vector<MapContainer> map_containers;
    std::vector<ShuffleContainer> shuffle_containers;

    Map map_obj;
    Shuffle shuffle_obj;
    Reduce reduce_obj;
};