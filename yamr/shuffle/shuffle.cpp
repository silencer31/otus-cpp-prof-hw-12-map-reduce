#include "shuffle.h"

#include <iostream>
#include <functional>


void Shuffle::run_threads()
{
    for (std::size_t index = 0; index < static_cast<std::size_t>(map_threads_number); ++index)
        shuffle_threads.emplace_back(std::thread(&Shuffle::thread_proc, this, index));

    wait_for_finished();
}

void Shuffle::wait_for_finished()
{
    for (auto& thread : shuffle_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Shuffle::thread_proc(std::size_t cont_index)
{
    try
    {
        shuffle_worker(cont_index);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}


std::size_t Shuffle::reduce_index(const std::string& line) const
{
    std::hash<std::string> hashFn;

    return hashFn(line) % reduce_threads_number;
}

void Shuffle::shuffle_worker(std::size_t cont_index)
{
    MapContainer& container = map_containers[cont_index];
    
    for (const auto& line : container.cont_strings)
    {
        std::size_t index = reduce_index(line);

        shuffle_containers[index].insert_line(line);
    }
}
