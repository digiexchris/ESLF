// #include "Logging/Logger.hpp"
// #include "Mocks/Logging/MockLogBackend.hpp"
// #include "TestHelpers/Logging/LoggingUnitTest.hpp"

// #include <catch2/catch_test_macros.hpp>
// #include <catch2/matchers/catch_matchers_string.hpp>
// #include <catch2/trompeloeil.hpp>
// #include <iostream>

// using namespace Mocks::Logging;

// using Catch::Matchers::Equals;

// class LoggerTest {

// public:
//   LoggerTest() {
//     uint32_t uniqueId1 = 0;
//     uint32_t uniqueId2 = 0;


//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<uint32_t> dis(1, UINT32_MAX); // Adjust the range as needed
//     uniqueId1 = dis(gen);
//     uniqueId2 = dis(gen);
//     int tries = 10;
//     while(uniqueId1 == uniqueId2) { //an attempt to not make this test flakey on the off chance that the random number generator generates the same number twice
//       REQUIRE_FALSE(tries == 0); //an attempt to not let this loop run forever
//       uniqueId2 = dis(gen);
//       tries--;
//     }

//     mockLogBackend = new MockLogBackend(uniqueId1);
//     mockLogBackend2 = new MockLogBackend(uniqueId2);
//   }
//   ~LoggerTest() {
//     //NOTE: since this is managed by the Logger singleton, we consider the backend transferred to the singleton and do not own it anymore.
//     // We should not delete or otherwise manage  that memory.
//   }

// protected:
//   MockLogBackend* mockLogBackend = nullptr;
//   MockLogBackend* mockLogBackend2 = nullptr;
// };

// TEST_CASE_METHOD(LoggerTest, "LoggerInitException_what_returns_correct_string", "[Logger]")
// {
//   LoggerInitException e = LOGGER_INIT_EXCEPTION("FOO");
//   REQUIRE_THAT(e.what(),Equals( "FOO"));
// }

// TEST_CASE_METHOD(LoggerTest, "create_and_destroy_logger", "[Logger]")
// {
//   LogSingleton::create(std::move(mockLogBackend));
//   REQUIRE(LogSingleton::is_valid());
//   LogSingleton::destroy();
// }

// TEST_CASE_METHOD(LoggerTest, "use_without_create_throws", "[Logger]")
// {

//   REQUIRE_THROWS_AS(
//     LogSingleton::instance().Info("Foo")
//   ,etl::singleton_not_created);

//   REQUIRE_THROWS_AS(
//     LogSingleton::instance().Warn("Foo")
//   ,etl::singleton_not_created);

//   REQUIRE_THROWS_AS(
//     // Log<256>::Init(nullptr);
//     LogSingleton::instance().Error("Foo")
//   ,etl::singleton_not_created);
// }

// TEST_CASE_METHOD(LoggerTest, "init_with_valid_backend_does_not_throw_and_can_log", "[Logger]")
// {
//   REQUIRE_CALL(*mockLogBackend, Info("Foo")).TIMES(1);
//   REQUIRE_CALL(*mockLogBackend, Warn("FooWarn")).TIMES(1);
//   REQUIRE_CALL(*mockLogBackend, Error("FooError")).TIMES(1);

//   LogSingleton::create(std::move(mockLogBackend));
//   REQUIRE(LogSingleton::is_valid());

//   LogSingleton::instance().Info("Foo");
//   LogSingleton::instance().Warn("FooWarn");
//   LogSingleton::instance().Error("FooError");
  
//   REQUIRE_CALL(*mockLogBackend, Warn("Foo2")).TIMES(1);
//   LogSingleton::instance().Warn("Foo2");

//   REQUIRE_CALL(*mockLogBackend, Error("Foo3")).TIMES(1);
//   LogSingleton::instance().Error("Foo3");
// }

// #include <random>
// TEST_CASE_METHOD(LoggerTest, "init_while_already_initialized_ignores_create", "[Logger]")
// {
//   // bool result1 = 
//   LogSingleton::create(std::move(mockLogBackend));

//   LogSingleton::create(std::move(mockLogBackend2));

//   REQUIRE(LogSingleton::is_valid());

//   REQUIRE(static_cast<MockLogBackend*>(LogSingleton::instance().GetBackend())->uniqueId == mockLogBackend->uniqueId);

  
// }

// TEST_CASE_METHOD(LoggerTest, "macro_use_without_init_throws", "[Logger]")
// {

//   REQUIRE_THROWS_AS(
//     LogSingleton::instance().Info("Foo")
//     ,etl::singleton_not_created
//   );
// }