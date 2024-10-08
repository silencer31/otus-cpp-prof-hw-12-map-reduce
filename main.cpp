#include "external_functions.h"
#include "options_reader/options_reader.h"
#include "yamr/map_reduce/map_reduce.h"

#include <memory>
#include <iostream>

#include <boost/filesystem/operations.hpp>


int main(int args_number, char const** args)
{   
    // ������ ��� ������ ���������� - ���������� ���������.
    const std::unique_ptr<OptionsReader> opt_reader_ptr = std::make_unique<OptionsReader>();
    
    // ����� ���������� - ���������� ���������.
    const Parameters parameters = opt_reader_ptr->read_arguments(args_number, args);
    
    if (parameters.show_help) {
        std::cerr << parameters.help_text << std::endl;
        return 0;
    }
   
    // ���������, ���������� �� ����.
    if (!boost::filesystem::exists(parameters.src)) {
        std::cerr << "Provided file doesn't exist! " << parameters.src << std::endl;;
        return -1;
    }
    
    // ���������, �� ������ �� ����.
    if (boost::filesystem::is_empty(parameters.src)) {
        std::cerr << "Provided file is empty! " << parameters.src << std::endl;;
        return -1;
    }

    // ��������� ����� - ����� ������ ��� ������� map.
    std::set<uint64_t> block_points = 
        get_file_block_points(parameters.src, parameters.mnum);

    // ��������� �� ����� �� ��������� �����.
    if (block_points.empty()) {
        std::cerr << "Unable to divide file to blocks! " << parameters.src << std::endl;;
        return -1;
    }

    std::cout << "MapReduce parameters:" << std::endl;
    std::cout << "  File path: " << parameters.src << std::endl;
    std::cout << "  Map threads number:" << parameters.mnum << std::endl;
    std::cout << "  Reduce Map threads number:" << parameters.rnum << std::endl;

    MapReduce map_reduce(parameters.src, parameters.mnum, parameters.rnum, std::move(block_points));
    map_reduce.start();

    return 0;
}