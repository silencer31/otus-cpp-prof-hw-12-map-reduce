#pragma once

#include <string>
#include <set>
#include <mutex>

/**
* @brief ��������� ��� ����� �����������.
*/
struct MapContainer
{
    void insert_line(const std::string& str);

    std::multiset<std::string> cont_strings;
};

extern std::mutex map_mutex;

/**
* @brief ��������� ��� ����� ������.
*/
struct ShuffleContainer
{
    void insert_line(const std::string& str);

    std::multiset<std::string> cont_strings;
};

extern std::mutex shuffle_mutex;