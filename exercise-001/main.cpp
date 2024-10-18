#include <fmt/chrono.h>
#include <fmt/format.h>
#include <random>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};

    

    auto counter(20);
    
   
    try
    {   
        app.add_option("-c,--count", counter, "How many items to insert");

        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    auto start = std::chrono::system_clock::now();

    std::vector<int> numbers(counter);

    srand(time(0));

    for (int &number : numbers)
    {
        number = rand() % 100 + 1;
    }

    std::sort(numbers.begin(), numbers.end());

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    fmt::print("Elapsed time: {} ms\n", elapsed.count());

    fmt::print("Numbers: ");
    for (const auto &number : numbers)
    {
        fmt::print("{} ", number);
    }

    fmt::print("Hello, {}!\n", app.get_name());

    fmt::print("Count: {}\n", counter);

    

    return 0; /* exit gracefully*/
}
