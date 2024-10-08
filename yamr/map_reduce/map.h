#pragma once

#include "../containers/containers.h"
#include "../functors/functors.h"

#include <thread>

/**
* @brief ����� ��������� ���� Map
*/
class Map
{
public:
    Map(const std::string& file_path, std::vector<MapContainer>& containers)
        : src_file_path(file_path)
        , map_containers(containers)
    {}

    /**
    * ������ �������.
    * �������� ���-�� ������� Map ����� �� ������������, �.�. �� ���-�� ����� ���-�� �������������� ������ �����.
    * @param block_points ��������� ������� � ����� ��� ������ ������ ������� ������ Map.
    */
    void run_threads(const std::set<uint64_t>& block_points);

private:
    /**
    * �������� ���������� ���� �������.
    */
    void wait_for_finished();

    /**
    * ����� ��� ������ � ��������� ������.
    * @param min_offset ��������� ������� ������
    * @param max_offset ������������ ������� ������
    * @param last_block ����, ����������� �� ��������� ���������� �����
    * @param cont_index ������ ��� ����������� Map
    */
    void thread_proc(uint64_t min_offset, uint64_t max_offset, bool last_block, std::size_t cont_index);

    /**
    * ��������� ����� � �������.
    * @param min_offset ��������� ������� ������
    * @param max_offset ������������ ������� ������
    * @param last_block ����, ����������� �� ��������� ���������� �����
    * @param cont_index ������ ��� ����������� Map
    */
    void handle_file_block(uint64_t min_offset, uint64_t max_offset, bool last_block, std::size_t cont_index);

    const std::string src_file_path;

    std::vector<std::thread> map_threads;
    std::vector<MapContainer>& map_containers;
};