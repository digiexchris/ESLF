#include "setup.hpp"

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    // Global environment registration
    ::testing::AddGlobalTestEnvironment(new ELSFEnvironment);
    return RUN_ALL_TESTS();
}
