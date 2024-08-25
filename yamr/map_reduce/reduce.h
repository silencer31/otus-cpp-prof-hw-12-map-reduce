#pragma once

#include "../containers/containers.h"
#include "../functors/functors.h"

#include <thread>

class Reduce
{
public:
    Reduce(int threads_number, std::vector<ShuffleContainer>& containers)
        : reduce_threads_number(threads_number)
        , shuffle_containers(containers)
    {}

    void run_threads();

private:
    void wait_for_finished();

    void thread_proc(std::size_t cont_index);

    void reduce_worker(std::size_t cont_index);

    const int reduce_threads_number;

    std::vector<ShuffleContainer>& shuffle_containers;
    std::vector<std::thread> reduce_threads;
};
