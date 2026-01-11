
#include "CSVDataExporter.hpp"

#include <format>

DataExporter::DataExporter(const std::string& fileName_, const std::string& filePath_)
    : fileName(fileName_)
    , filePath(filePath_)
{
    file.open(filePath + fileName);

    if (!file.is_open())
        throw std::runtime_error(std::format("Failed to open file: {}{}", filePath, fileName));
};

DataExporter::~DataExporter()
{
    if (file.is_open())
    {
        file.flush();
        file.close();
    }
}
