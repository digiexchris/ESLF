#include "Logging/Logger.hpp"
#include "gtest/gtest.h"

TEST(Logger, use_without_create_throws) {
    

    ASSERT_THROW({
    //Log<256>::Init(nullptr);
    auto instance = LogSingleton::instance();
    instance.Info("Foo");

    //rework this logger so that Log::Info() calls LogSingleton::instance().Info() if LogSingleton::has_instance() otherwise throw an
  }, etl::singleton_not_created);
}

TEST(Logger, macro_use_without_init_throws) {
    

    ASSERT_THROW({
    //Log<256>::Init(nullptr);
    ELSF_LOG_INFO("Foo");

    //rework this logger so that Log::Info() calls LogSingleton::instance().Info() if LogSingleton::has_instance() otherwise throw an
  }, LoggerInitException);
}