#pragma once

#include <filesystem>
namespace Playground::IO
{
    /**
     * open a file a read all his content in a dynamically allocated char *
     */

    char *read_file(const std::filesystem::path &file_path);

} // namespace Playground::IO
