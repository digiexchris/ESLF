#include "Logging/Logger.hpp"
#include <gtest/gtest.h>

#include <gmock/gmock.h> // Include the necessary header file
#include "Mocks/Logging/MockLogBackend.hpp"

using namespace Mocks::Logging;

class LoggerTest : public testing::Test {
protected:
  void TearDown() override {
    if(LogSingleton::is_valid()) {
      LogSingleton::destroy();
    }
  }
};

class LoggerExceptionTest : public testing::Test {
protected:
};

TEST_F(LoggerExceptionTest, LoggerInitException_what_returns_correct_string)
{
  LoggerInitException e = LOGGER_INIT_EXCEPTION("FOO");
  EXPECT_STREQ(e.what(), "FOO");
}

//Note: this mockLogBackend must be a stack var, not a pointer, unless you manage it's memory manually
TEST_F(LoggerTest, create_and_destroy_logger)
{
  MockLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH> mockLogBackend;
  LogSingleton::create(mockLogBackend);
  LogSingleton::destroy();
}

TEST_F(LoggerTest, use_without_create_throws)
{

  ASSERT_THROW({
    // Log<256>::Init(nullptr);
    LogSingleton::instance().Info("Foo");
  },etl::singleton_not_created);

  ASSERT_THROW({
    // Log<256>::Init(nullptr);
    LogSingleton::instance().Warn("Foo");
  },etl::singleton_not_created);

  ASSERT_THROW({
    // Log<256>::Init(nullptr);
    LogSingleton::instance().Error("Foo");
  },etl::singleton_not_created);
}

TEST_F(LoggerTest, init_with_valid_backend_does_not_throw_and_can_log)
{
  MockLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH> mockLogBackend;
  EXPECT_CALL(mockLogBackend, LogFormattedInfo("Foo")).Times(testing::Exactly(1));
  EXPECT_CALL(mockLogBackend, LogFormattedWarn("FooWarn")).Times(testing::Exactly(1));
  EXPECT_CALL(mockLogBackend, LogFormattedError("FooError")).Times(testing::Exactly(1));

  bool result = LogFactory<256>::Create(mockLogBackend);
  ASSERT_TRUE(result);

  LogSingleton::instance().Info("Foo");
  LogSingleton::instance().Warn("FooWarn");
  LogSingleton::instance().Error("FooError");
  
  EXPECT_CALL(mockLogBackend, LogFormattedWarn("Foo2")).Times(testing::Exactly(1));
  Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Warn("Foo2");

  EXPECT_CALL(mockLogBackend, LogFormattedError("Foo3")).Times(testing::Exactly(1));
  Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Error("Foo3");
}

#include <random>
TEST_F(LoggerTest, init_while_already_initialized_asserts)
{
  uint32_t uniqueId1 = 0;
  uint32_t uniqueId2 = 0;


  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> dis(1, UINT32_MAX); // Adjust the range as needed
  uniqueId1 = dis(gen);
  uniqueId2 = dis(gen);
  int tries = 10;
  while(uniqueId1 == uniqueId2) { //an attempt to not make this test flakey on the off chance that the random number generator generates the same number twice
    ASSERT_GT(tries, 0); //an attempt to not let this loop run forever
    uniqueId2 = dis(gen);
    tries--;
  }

  MockLogBackend<256ULL> mockLogBackend1(uniqueId1);
  MockLogBackend<256ULL> mockLogBackend2(uniqueId2);

  // bool result1 = 
  LogFactory<256>::Create(mockLogBackend1);

  ASSERT_THROW({
    LogFactory<256>::Create(mockLogBackend2);
  }, LoggerInitException);
}

TEST_F(LoggerTest, macro_use_without_init_throws)
{

  ASSERT_THROW({
    ELSF_LOG_INFO("Foo");

    },
               etl::singleton_not_created);
}