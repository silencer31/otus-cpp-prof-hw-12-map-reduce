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
* @brief Класс реализует чтение параметров программы.
*/
class OptionsReader {
public:

    /**
    * @brief Прочитать аргументы, с которыми была запущена программа.
    * @param argc кол-во аргументов.
    * @param argv аргуметны.
    * @return Структура с прочитанными параметрами.
    */
    Parameters read_arguments(int argc, const char* argv[]);

private:

    /**
    * @brief Проверить, что значение не является отрицательным.
    */
    template <typename T>
    static void check_value_is_not_negative(const T& value, std::string option_name);
};