#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

/**
* @brief ����� ������� ��� ���������� ����� ����������� - Map.
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
* @brief ����� ������� ��� ���������� ����� ������ - Reduce.
*/
class ReduceFunctor
{
public:
    std::size_t operator() (const std::multiset<std::string>& lines);

private:
    std::unordered_map<std::string, int> counters; // prefix -> count
};
