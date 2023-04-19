add_executable(Tests tests.cpp world_tests.cpp)
target_link_libraries(Tests PRIVATE PongLib GTest::gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(Tests)