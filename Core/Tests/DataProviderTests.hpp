#pragma once

#include <gtest/gtest.h>
#include "Gameplay/DataProvider.hpp"
#include "Game/Bird.hpp"
#include "Game/Pipes.hpp"
#include "DataProcessor/DataExporter.hpp"

class DataProviderFixture : public testing::Test
{
public:
    DataProvider dataProvider;
    DataExporter dataExporter{"test_data.csv", "Core/Tests/"};

    void TearDown() override;
};

TEST_F(DataProviderFixture, WriteHeaderTest)
{
    dataExporter.WriteHeader(dataProvider);

    std::ifstream file{"Core/Tests/test_data.csv"};
    std::string headerLine;
    std::getline(file, headerLine);

    EXPECT_EQ(headerLine, dataProvider.GetHeader());
};

void DataProviderFixture::TearDown()
{
    dataExporter.CloseFile();
    std::filesystem::remove("Core/Tests/test_data.csv");
}
