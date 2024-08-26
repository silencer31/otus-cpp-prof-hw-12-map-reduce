#pragma once

#include "../containers/containers.h"
#include "../functors/functors.h"

#include <thread>

/**
* @brief Класс реализует этап Reduce
*/
class Reduce
{
public:
    Reduce(unsigned int threads_number, std::vector<ShuffleContainer>& containers)
        : reduce_threads_number(threads_number)
        , shuffle_containers(containers)
    {}

    /**
    * Запуск потоков.
    */
    void run_threads();

private:
    /**
    * Ожидание завершения всех потоков.
    */
    void wait_for_finished();

    /**
    * Метод для работы в отдельном потоке.
    * @param cont_index Индекс для контейнеров Shuffle
    */
    void thread_proc(std::size_t cont_index);

    /**
    * Метод, выполняющий свёртку.
    * @param cont_index Индекс для контейнеров Shuffle
    */
    void reduce_worker(std::size_t cont_index);

    const unsigned int reduce_threads_number;

    std::vector<ShuffleContainer>& shuffle_containers;
    std::vector<std::thread> reduce_threads;
};
