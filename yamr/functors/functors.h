#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

/**
* @brief Класс функтор для реализации этапа отображения - Map.
*/
class MapFunctor
{
public:
    std::vector<std::string> operator() () const;

    void add_line(const std::string& line);

private:
    std::vector<std::string> map_lines;
};

/**
* @brief Класс функтор для реализации этапа свёртки - Reduce.
*/
class ReduceFunctor
{
public:
    std::size_t operator() (const std::multiset<std::string>& lines);

private:
    std::unordered_map<std::string, int> counters; // prefix -> count
};
