add_executable(SmokeTests tests.cpp)
target_link_libraries(SmokeTests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(SmokeTests)