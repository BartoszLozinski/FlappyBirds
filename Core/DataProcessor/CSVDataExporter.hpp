#pragma once

#include <string>
#include <concepts>
#include <fstream>
#include <filesystem>

template<typename DataStruct>
concept CSVExportable = requires(DataStruct data)
{
    { data.ToCSVRow() } -> std::convertible_to<std::string>;
    { data.WriteCSVHeader() } -> std::convertible_to<std::string>;
};

class DataExporter
{
private:
    std::string fileName{"data.csv"};
    std::string filePath{"./"};
    std::ofstream file{filePath + fileName};
    
public:

    DataExporter(const std::string& fileName_, const std::string& filePath_);
    ~DataExporter();
    DataExporter(const DataExporter&) = delete;
    DataExporter& operator=(const DataExporter&) = delete;
    DataExporter(DataExporter&&) = delete;
    DataExporter& operator=(DataExporter&&) = delete;
    
    template<CSVExportable DataStruct>
    void ExportRow(const DataStruct& dataStruct)
    {
        if (!file.is_open())
            file.open(filePath + fileName);

        if (file.is_open())
        {
            file << dataStruct.ToCSVRow() << "\n";
            file.flush();
        }
    };

    template<CSVExportable DataStruct>
    void WriteHeader(const DataStruct& dataStruct)
    {
        if (!file.is_open())
            file.open(filePath + fileName);

        if (file.is_open() && std::filesystem::exists(filePath + fileName) && std::filesystem::file_size(filePath + fileName) == 0)
        {
            file << dataStruct.WriteCSVHeader() << "\n";
            file.flush();
            file.close();
        }
    }
};