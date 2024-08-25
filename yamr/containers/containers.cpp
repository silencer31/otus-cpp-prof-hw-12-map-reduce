#include "containers.h"

void MapContainer::insert_line(const std::string& str)
{
    std::lock_guard<std::mutex> lock(map_mutex);
    cont_strings.insert(str);
}

std::mutex map_mutex;

void ShuffleContainer::insert_line(const std::string& str)
{
    std::lock_guard<std::mutex> lock(shuffle_mutex);
    cont_strings.insert(str);
}

std::mutex shuffle_mutex;