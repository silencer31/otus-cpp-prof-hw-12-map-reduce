#pragma once

#include "../containers/containers.h"
#include "../functors/functors.h"

#include <thread>

/**
* @brief Класс реализует этап Map
*/
class Map
{
public:
    Map(const std::string& file_path, std::vector<MapContainer>& containers)
        : src_file_path(file_path)
        , map_containers(containers)
    {}

    /**
    * Запуск потоков.
    * Параметр кол-во потоков Map здесь не используется, т.к. их кол-во равно кол-ву обрабатываемых блоков файла.
    * @param block_points Коллекция позиций в файле для начала работы каждого потока Map.
    */
    void run_threads(const std::set<uint64_t>& block_points);

private:
    /**
    * Ожидание завершения всех потоков.
    */
    void wait_for_finished();

    /**
    * Метод для работы в отдельном потоке.
    * @param min_offset Начальная позиция данных
    * @param max_offset Максимальная позиция данных
    * @param last_block Флаг, указывающий на обработку последнего блока
    * @param cont_index Индекс для контейнеров Map
    */
    void thread_proc(uint64_t min_offset, uint64_t max_offset, bool last_block, std::size_t cont_index);

    /**
    * Обработка файла с данными.
    * @param min_offset Начальная позиция данных
    * @param max_offset Максимальная позиция данных
    * @param last_block Флаг, указывающий на обработку последнего блока
    * @param cont_index Индекс для контейнеров Map
    */
    void handle_file_block(uint64_t min_offset, uint64_t max_offset, bool last_block, std::size_t cont_index);

    const std::string src_file_path;

    std::vector<std::thread> map_threads;
    std::vector<MapContainer>& map_containers;
};