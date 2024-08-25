#include "map_reduce.h"

MapReduce::MapReduce(const std::string& file_path,
    int mtn, int rtn,
    std::set<uint64_t>&& bp)
    : src_file_path(file_path)
    , map_threads_number(mtn)
    , reduce_threads_number(rtn)
    , block_points(bp)
{


    //mMapContainers.resize(aMapThreadsCount);
    //mShuffleContainers.resize(aReduceThreadsCount);
}

void MapReduce::start()
{
    /*mMap.Run(block_points);
    mShuffle.Run();
    mReduce.Run();*/
}