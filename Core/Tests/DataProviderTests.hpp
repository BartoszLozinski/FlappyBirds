#pragma once

#include <gtest/gtest.h>
#include "Gameplay/DataProvider.hpp"
#include "Game/Bird.hpp"
#include "Game/Pipes.hpp"

class DataProviderFixture : public testing::Test
{
public:
    Gameplay::DataProvider dataProvider;
};

//TO DO REWRITE TESTS FOR DATAPROVIDER