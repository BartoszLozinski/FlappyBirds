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

TEST_F(DataProviderFixture, ExportRowTest)
{
    Game::Bird bird;
    Game::Pipes pipes;

    dataProvider.SetState(bird, pipes);
    dataExporter.ExportRow(dataProvider);

    std::ifstream file{"Core/Tests/test_data.csv"};
    std::string dataLine;
    std::getline(file, dataLine);

    EXPECT_EQ(dataLine, dataProvider.GetRow());
};

TEST_F(DataProviderFixture, ExportRowWithHeaderTest)
{
    dataExporter.WriteHeader(dataProvider);

    Game::Bird bird;
    Game::Pipes pipes;

    dataProvider.SetState(bird, pipes);
    dataExporter.ExportRow(dataProvider);

    std::ifstream file{"Core/Tests/test_data.csv"};
    std::string headerLine;
    std::getline(file, headerLine);
    std::string dataLine;
    std::getline(file, dataLine);

    EXPECT_EQ(headerLine, dataProvider.GetHeader());
    EXPECT_EQ(dataLine, dataProvider.GetRow());
}

TEST_F(DataProviderFixture, Export3RowsWithHeaderTest)
{
    dataExporter.WriteHeader(dataProvider);
    static constexpr unsigned expectedLines = 4;

    Game::Bird bird;
    Game::Pipes pipes;

    for (unsigned i = 0; i < (expectedLines - 1); ++i)
    {
        dataProvider.SetState(bird, pipes);
        dataExporter.ExportRow(dataProvider);
        bird.UpdateState();
        pipes.UpdateState();
    }

    std::ifstream file{"Core/Tests/test_data.csv"};
    std::string headerLine;
    std::getline(file, headerLine);
    unsigned lineCount = 0;    
    
    while (!file.eof())
    {
        std::string dataLine;
        std::getline(file, dataLine);
        lineCount++;
    }

    EXPECT_EQ(headerLine, dataProvider.GetHeader());
    EXPECT_EQ(lineCount, expectedLines);
}

void DataProviderFixture::TearDown()
{
    std::filesystem::remove("Core/Tests/test_data.csv");
}
