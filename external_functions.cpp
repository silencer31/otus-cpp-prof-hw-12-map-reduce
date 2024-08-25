#include "external_functions.h"

#include <boost/filesystem.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

static uint64_t get_prev_line_start(uint64_t block_point, std::ifstream& src_stream)
{
    if (block_point == 0) { return 0; }
    
    char sym;
    src_stream.seekg(block_point);
    
    // Ищем точку окончания предыдущей строки.
    do {
        src_stream.read(&sym, 1);
        src_stream.seekg(-2, std::ios_base::cur);

    } while (sym != '\n' && sym != '\r' && src_stream.tellg() > 0);
    
    if (src_stream.tellg() == 0) { return 0; }

    src_stream.seekg(1, std::ios_base::cur);

    return src_stream.tellg();
}

std::set<uint64_t> get_file_block_points(const std::string& src_path, int threads_number)
{
    // Узнаем размер файла.
    const uint64_t src_file_size = boost::filesystem::file_size(src_path);

    // Размер блока для обработки потоком.
    const uint64_t one_part_size =
        static_cast<uint64_t>(std::ceil(static_cast<double>(src_file_size) / threads_number));

    // Коллекция точек начала обработки потоками.
    std::set<uint64_t> block_points;
    
    // Поток чтения файла.
    std::ifstream src_stream(src_path, std::ios::in | std::ios::binary);
    
    // Первая точка начала обработки потоком.
    uint64_t next_block_point = 0;
    block_points.emplace(next_block_point);
    next_block_point += one_part_size;
    
    // Вычисляем точки начала следующих блоков.
    while (next_block_point < src_file_size)
    {
        // Корректное начало предыдущей строки.
        uint64_t line_point = get_prev_line_start(next_block_point, src_stream);

        src_stream.seekg(line_point);
        char sym;
        
        do {
            src_stream.read(&sym, 1);
        }
        while (
            (sym == '\n' || sym == '\r') &&
            static_cast<uint64_t>(src_stream.tellg()) < src_file_size);
        
        src_stream.seekg(-1, std::ios_base::cur);

        auto result = block_points.emplace(src_stream.tellg());

        if (!result.second) { return std::set<uint64_t>(); }
        
        next_block_point += one_part_size;
    }

    return block_points;
}