#pragma once

#include "../containers/containers.h"
#include "../functors/functors.h"

#include <thread>

class Map
{
public:
    Map(const std::string& aSrcFileName, int aThreadsCount, std::vector<MapContainer>& aMapContainers);

    void Run(const std::set<uint64_t>& aOffsets);

private:
    void WaitThreads();
    void ThreadProc(uint64_t aMinOffset, uint64_t aMaxOffset, std::size_t aIndex);
    void Worker(uint64_t aMinOffset, uint64_t aMaxOffset, std::size_t aIndex);

    std::string mSrcFileName;
    int mThreadsCount;

    std::vector<std::thread> mThreads;
    std::vector<MapContainer>& mMapContainers;
};