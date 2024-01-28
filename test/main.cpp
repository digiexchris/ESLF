#include "setup.hpp"

#include <gtest/gtest.h>

auto env = testing::AddGlobalTestEnvironment(new ELSFEnvironment);
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    // Global environment registration
    // testing::AddGlobalTestEnvironment(new ELSFEnvironment);
    //ELSF_LOG_INIT(new TestLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH, 8>());
    return RUN_ALL_TESTS();
}

