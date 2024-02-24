#include "Logging/Logger.hpp"
#include "Mocks/Logging/MockLogBackend.hpp"
#include "TestHelpers/Logging/LoggingUnitTest.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <trompeloeil.hpp>

using namespace Mocks::Logging;

using Catch::Matchers::Equals;

class LoggerExceptionTest {
protected:
};

TEST_CASE_METHOD(LoggerExceptionTest, "LoggerInitException_what_returns_correct_string", "[Logger]")
{
  LoggerInitException e = LOGGER_INIT_EXCEPTION("FOO");
  REQUIRE_THAT(e.what(),Equals( "FOO"));
}

//Note: this mockLogBackend must be a stack var, not a pointer, unless you manage it's memory manually
TEST_CASE_METHOD(LoggerTest, "create_and_destroy_logger")
{
  MockLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH> mockLogBackend;
  LogSingleton::create(mockLogBackend);
  LogSingleton::destroy();
}

TEST_CASE_METHOD(LoggerTest, "use_without_create_throws")
{

  REQUIRE_THROWS_AS(
    LogSingleton::instance().Info("Foo")
  ,etl::singleton_not_created);

  REQUIRE_THROWS_AS(
    LogSingleton::instance().Warn("Foo")
  ,etl::singleton_not_created);

  REQUIRE_THROWS_AS(
    // Log<256>::Init(nullptr);
    LogSingleton::instance().Error("Foo")
  ,etl::singleton_not_created);
}

TEST_CASE_METHOD(LoggerTest, "init_with_valid_backend_does_not_throw_and_can_log")
{
  MockLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH> mockLogBackend;
  REQUIRE_CALL(mockLogBackend, InfoMock("Foo")).TIMES(1);
  REQUIRE_CALL(mockLogBackend, WarnMock("FooWarn")).TIMES(1);
  REQUIRE_CALL(mockLogBackend, ErrorMock("FooError")).TIMES(1);

  bool result = LogFactory<256>::Create(mockLogBackend);
  REQUIRE(result);

  LogSingleton::instance().Info("Foo");
  LogSingleton::instance().Warn("FooWarn");
  LogSingleton::instance().Error("FooError");
  
  REQUIRE_CALL(mockLogBackend, WarnMock("Foo2")).TIMES(1);
  Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Warn("Foo2");

  REQUIRE_CALL(mockLogBackend, ErrorMock("Foo3")).TIMES(1);
  Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Error("Foo3");
}

#include <random>
TEST_CASE_METHOD(LoggerTest, "init_while_already_initialized_asserts")
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
    REQUIRE_FALSE(tries == 0); //an attempt to not let this loop run forever
    uniqueId2 = dis(gen);
    tries--;
  }

  MockLogBackend<256ULL> mockLogBackend1(uniqueId1);
  MockLogBackend<256ULL> mockLogBackend2(uniqueId2);

  // bool result1 = 
  LogFactory<256>::Create(mockLogBackend1);

  REQUIRE_THROWS_AS(
    LogFactory<256>::Create(mockLogBackend2)
  , LoggerInitException);
}

TEST_CASE_METHOD(LoggerTest, "macro_use_without_init_throws")
{

  REQUIRE_THROWS_AS(
    ELSF_LOG_INFO("Foo")
    ,etl::singleton_not_created
  );
}