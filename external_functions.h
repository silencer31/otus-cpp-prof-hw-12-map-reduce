#pragma once

#include <stdint.h>
#include <set>
#include <string>

/**
* Обработка ввода.
* @return Коллекция позиций в файле для начала работы каждого потока Map.
* @param src_path Путь к обрабатываемому файлу.
* @param threads_number Кол-во потоков.
*/
std::set<uint64_t> get_file_block_points(const std::string& src_path, int threads_number);