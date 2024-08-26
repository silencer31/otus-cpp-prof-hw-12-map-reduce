#pragma once

#include "map.h"
#include "reduce.h"
#include "../shuffle/shuffle.h"

#include <stdint.h>

/**
* @brief Класс реализует систему запуска задач MapReduce
*/
class MapReduce
{
public:
    MapReduce(const std::string& src_file_path,
        unsigned int map_threads_number, unsigned int reduce_threads_number,
        std::set<uint64_t>&& bp);

    /**
    * Запуск работы системы задач MapReduce.
    */
    void start();

private:
    // Коллекция позиций в файле для начала работы каждого потока Map.
    const std::set<uint64_t> block_points;
    
    std::vector<MapContainer> map_containers;
    std::vector<ShuffleContainer> shuffle_containers;

    Map map_obj;
    Shuffle shuffle_obj;
    Reduce reduce_obj;
};