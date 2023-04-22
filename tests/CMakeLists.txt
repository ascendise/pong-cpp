add_executable(Tests tests.cpp world_tests.cpp "test_doubles/fakes/fake_component.cpp" "test_doubles/fakes/fake_system.cpp")
target_link_libraries(Tests PRIVATE PongLib GTest::gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(Tests)