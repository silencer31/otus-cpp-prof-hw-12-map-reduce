#pragma once

#include "../containers/containers.h"
#include "../functors/functors.h"

#include <thread>

class Map
{
public:
    Map(const std::string& file_path, std::vector<MapContainer>& containers)
        : src_file_path(file_path)
        , map_containers(containers)
    {}


    void run_threads(const std::set<uint64_t>& block_points);

private:
    void wait_for_finished();

    void thread_proc(uint64_t min_offset, uint64_t max_offset, std::size_t cont_index);

    void handle_file_block(uint64_t min_offset, uint64_t max_offset, std::size_t cont_index);

    const std::string src_file_path;

    std::vector<std::thread> map_threads;
    std::vector<MapContainer>& map_containers;
};