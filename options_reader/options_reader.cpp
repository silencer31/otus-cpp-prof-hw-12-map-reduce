#include "options_reader.h"

#include <boost/program_options.hpp>
#include <boost/any.hpp>

using namespace std;
namespace po = boost::program_options;

Parameters OptionsReader::read_arguments(int argc, const char* argv[])
{
    po::options_description desc("MapReduce app. Parameters");
    
    desc.add_options()
        ("help,h", "Outputs help information")
        ("src,s",
            po::value<string>()->default_value("strings.txt"),
            "Path to file with strings to sort.")
        ("mnum,m",
            po::value<int>()->default_value(4)->notifier([](const int& value)
                {
                    check_value_is_not_negative(value, "mnum");
                }),
            "Number of threads for map.")
        ("rnum,r",
            po::value<int>()->default_value(4)->notifier([](const int& value)
                {
                    check_value_is_not_negative(value, "rnum");
                }),
            "Number of threads for reduce.")
        ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    notify(vm);

    stringstream help;
    help << desc << endl;

    Parameters parameters;

    parameters.help_text = help.str();
    parameters.show_help = vm.count("help");

    if (parameters.show_help) {
        return parameters;
    }
    
    // Путь к файлу.
    parameters.src = vm["src"].as<string>();
    
    // Количество потоков для работы отображения.
    if (vm.count("mnum")) {
        parameters.mnum = static_cast<unsigned int>(vm["mnum"].as<int>());
    }
    
    // Количество потоков для работы свертки.
    if (vm.count("rnum")) {
        parameters.rnum = static_cast<unsigned int>(vm["rnum"].as<int>());
    }
    
    return parameters;
}

template <typename T>
void OptionsReader::check_value_is_not_negative(const T& value, std::string option_name)
{
    if (value < 0) {
        throw po::validation_error(po::validation_error::invalid_option_value, option_name);
    }
}