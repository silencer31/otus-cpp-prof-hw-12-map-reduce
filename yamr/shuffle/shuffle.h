#pragma once

#include "../containers/containers.h"

#include <vector>
#include <thread>

/**
* @brief ����� ��������� ���� Shuffle
*/
class Shuffle
{
public:
    Shuffle(int map_tn, int reduce_tn,        
        std::vector<MapContainer>& m_conts,
        std::vector<ShuffleContainer>& s_conts)
        : map_threads_number(map_tn)
        , reduce_threads_number(reduce_tn)
        , map_containers(m_conts)
        , shuffle_containers(s_conts)
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
    * �����, ����������� ������.
    * @param cont_index ������ ��� ����������� Shuffle
    */
    void thread_proc(std::size_t cont_index);
    
    std::size_t reduce_index(const std::string& line) const;
    
    /**
    * �����, ����������� ����������.
    * @param cont_index ������ ��� ����������� Map
    */
    void shuffle_worker(std::size_t cont_index);

    const unsigned int map_threads_number;
    const unsigned int reduce_threads_number;

    std::vector<MapContainer>& map_containers;
    std::vector<ShuffleContainer>& shuffle_containers;

    std::vector<std::thread> shuffle_threads;
};
