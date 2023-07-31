#include "utils/io/io.hh"

#include <filesystem>
#include <fstream>
#include <ios>

namespace Playground::IO
{
    char *read_file(const std::filesystem::path &file_path)
    {
        std::ifstream input(file_path, std::ios::ate);

        size_t size = input.tellg();
        char *str = new char[size + 1]();
        input.seekg(0);
        input.read(str, size);

        return str;
    }
} // namespace Playground::IO
