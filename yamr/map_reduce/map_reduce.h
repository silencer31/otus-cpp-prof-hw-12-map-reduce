#pragma once

#include <stdint.h>
#include <set>
#include <string>

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
    /*
    std::vector<MapContainer> mMapContainers;
    std::vector<ShuffleContainer> mShuffleContainers;

    Map mMap;
    Shuffle mShuffle;
    Reduce mReduce;*/
};