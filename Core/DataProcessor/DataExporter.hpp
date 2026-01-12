#pragma once

#include <string>
#include <concepts>
#include <fstream>
#include <filesystem>

template<typename DataStruct>
concept CSVExportable = requires(DataStruct data)
{
    { data.GetRow() } -> std::convertible_to<std::string>;
    { data.GetHeader() } -> std::convertible_to<std::string>;
};

class DataExporter
{
private:
    std::string fileName{"data.csv"};
    std::string filePath{"./"};
    std::ofstream file{};
    
public:

    DataExporter(const std::string& fileName_, const std::string& filePath_);
    ~DataExporter();
    DataExporter(const DataExporter&) = delete;
    DataExporter& operator=(const DataExporter&) = delete;
    DataExporter(DataExporter&&) = delete;
    DataExporter& operator=(DataExporter&&) = delete;
    
    template<CSVExportable DataProvider>
    void ExportRow(const DataProvider& dataProvider)
    {
        if (!file.is_open())
            file.open(filePath + fileName, std::ios::app);

        if (file.is_open())
        {
            file << dataProvider.GetRow() << "\n";
            file.flush();
            file.close();
        }
    };

    template<CSVExportable DataProvider>
    void WriteHeader(const DataProvider& dataProvider)
    {
        if (!file.is_open())
            file.open(filePath + fileName, std::ios::app);

        if (file.is_open() && std::filesystem::exists(filePath + fileName) && std::filesystem::file_size(filePath + fileName) == 0)
        {
            file << dataProvider.GetHeader() << "\n";
            file.flush();
            file.close();
        }
    }
};