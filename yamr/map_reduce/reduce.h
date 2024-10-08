#pragma once

#include "../containers/containers.h"
#include "../functors/functors.h"

#include <thread>

/**
* @brief ����� ��������� ���� Reduce
*/
class Reduce
{
public:
    Reduce(unsigned int threads_number, std::vector<ShuffleContainer>& containers)
        : reduce_threads_number(threads_number)
        , shuffle_containers(containers)
    {}

    /**
    * ������ �������.
    */
    void run_threads();

private:
    /**
    * �������� ���������� ���� �������.
    */
    void wait_for_finished();

    /**
    * ����� ��� ������ � ��������� ������.
    * @param cont_index ������ ��� ����������� Shuffle
    */
    void thread_proc(std::size_t cont_index);

    /**
    * �����, ����������� ������.
    * @param cont_index ������ ��� ����������� Shuffle
    */
    void reduce_worker(std::size_t cont_index);

    const unsigned int reduce_threads_number;

    std::vector<ShuffleContainer>& shuffle_containers;
    std::vector<std::thread> reduce_threads;
};
