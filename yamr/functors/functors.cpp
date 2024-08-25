#include <string>

#include "functors.h"

void MapFunctor::add_line(const std::string& line)
{
    for (std::size_t index = 1; index <= line.length(); ++index)
        map_lines.push_back(line.substr(0, index));
}

std::vector<std::string> MapFunctor::operator() () const
{
    return map_lines;
}

std::size_t ReduceFunctor::operator() (const std::multiset<std::string>& lines)
{
    std::size_t maxLength = 0;
    
    for (const std::string& line : lines)
    {

        int size = ++counters[line];
        if (size > 1 && line.length() > maxLength)
        {

            maxLength = line.length();
        }
    }
    return maxLength + 1;
}



