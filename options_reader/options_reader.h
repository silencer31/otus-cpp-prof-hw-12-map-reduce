#pragma once

#include <string>

struct Parameters
{
    unsigned int mnum{ 0 };
    unsigned int rnum{ 0 };
    std::string src;

    bool show_help{ false };
    std::string help_text;
};

/**
* @brief ����� ��������� ������ ���������� ���������.
*/
class OptionsReader {
public:

    /**
    * @brief ��������� ���������, � �������� ���� �������� ���������.
    * @param argc ���-�� ����������.
    * @param argv ���������.
    * @return ��������� � ������������ �����������.
    */
    Parameters read_arguments(int argc, const char* argv[]);

private:

    /**
    * @brief ���������, ��� �������� �� �������� �������������.
    */
    template <typename T>
    static void check_value_is_not_negative(const T& value, std::string option_name);
};