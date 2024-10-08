#pragma once

#include <stdint.h>
#include <set>
#include <string>

/**
* ��������� �����.
* @return ��������� ������� � ����� ��� ������ ������ ������� ������ Map.
* @param src_path ���� � ��������������� �����.
* @param threads_number ���-�� �������.
*/
std::set<uint64_t> get_file_block_points(const std::string& src_path, int threads_number);