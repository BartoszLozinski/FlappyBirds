
#include "DataExporter.hpp"

#include <format>

DataExporter::DataExporter(const std::string& fileName_, const std::string& filePath_)
    : fileName(fileName_)
    , filePath(filePath_)
{};

DataExporter::~DataExporter()
{
    CloseFile();
}

void DataExporter::CloseFile()
{
    if (file.is_open())
    {
        file.flush();
        file.close();
    }
}
