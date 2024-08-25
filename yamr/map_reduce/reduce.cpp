#include "reduce.h"

#include <iostream>
#include <fstream>
#include <sstream>

void Reduce::run_threads()
{
    for (std::size_t index = 0; index < static_cast<std::size_t>(reduce_threads_number); ++index)
    {
        reduce_threads.emplace_back(std::thread(&Reduce::thread_proc, this, index));
    }

    wait_for_finished();
}

void Reduce::wait_for_finished()
{
    for (auto& thread : reduce_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Reduce::thread_proc(std::size_t cont_index)
{
    try
    {
        reduce_worker(cont_index);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Reduce::reduce_worker(std::size_t cont_ndex)
{
    ShuffleContainer& container = shuffle_containers[cont_ndex];

    std::stringstream file_name;
    file_name << "reduced_" << cont_ndex;
    std::ofstream file_stream(file_name.str());
    
    ReduceFunctor functor;
    file_stream << functor(container.cont_strings);
}

