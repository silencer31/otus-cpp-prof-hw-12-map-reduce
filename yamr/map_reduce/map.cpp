#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "map.h"

Map::Map(const std::string& aSrcFileName, int aMapThreadsCount, std::vector<MapContainer>& aMapContainers)
    : mSrcFileName(aSrcFileName)
    , mThreadsCount(aMapThreadsCount)
    , mMapContainers(aMapContainers)
{
}

void Map::Run(const std::set<uint64_t>& aOffsets)
{
    std::vector<uint64_t> offsets(aOffsets.begin(), aOffsets.end());
    
    for (std::size_t index = 0; index < offsets.size(); ++index)
    {
        uint64_t minOffset = offsets[index];
        uint64_t maxOffset = index + 1 < offsets.size() ? offsets[index + 1] : -1;
        
        mThreads.emplace_back(std::thread(&Map::ThreadProc, this, minOffset, maxOffset, index));
    }
    WaitThreads();
}

void Map::WaitThreads()
{
    for (auto& thread : mThreads)
        if (thread.joinable())
            thread.join();
}

void Map::ThreadProc(uint64_t aMinOffset, uint64_t aMaxOffset, std::size_t aIndex)
{
    try
    {
        Worker(aMinOffset, aMaxOffset, aIndex);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Map::Worker(uint64_t aMinOffset, uint64_t aMaxOffset, std::size_t aIndex)
{
    MapFunctor functor;

    //assert(aMaxOffset == 1 || aMaxOffset >= aMinOffset);
    std::ifstream src_stream(mSrcFileName);
    src_stream.seekg(aMinOffset);
    std::string file_line;
    MapContainer& container = mMapContainers[aIndex];

    while (std::getline(src_stream, file_line) && (aMaxOffset == -1 || static_cast<uint64_t>(src_stream.tellg()) <= aMaxOffset))
    {
        if (file_line.length() > 0 && file_line[file_line.length() - 1] == '\r')
            file_line = file_line.substr(0, file_line.length() - 1);

        functor.AddLine(file_line);
    }

    for (const std::string& line : functor()) {
        container.Insert(line);
    }
}
