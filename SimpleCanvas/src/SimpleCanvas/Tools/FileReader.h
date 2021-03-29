#pragma once

#include <fstream>
#include <string>

namespace sc
{
class FileReader
{
public:
    FileReader() = default;
    ~FileReader() = default;
    
    std::string readFile(std::string const& filePath)
    {
        std::ifstream infile(filePath);
        if (!infile.is_open())
        {
            LOG_ERROR("Could not open file. Path: %s", filePath.c_str());
            return "";
        }

        std::string result, line;
        while (std::getline(infile, line))
        {
            result += line + '\n';
        }
        result.pop_back();

        return result;
    }
};
} // namespace sc