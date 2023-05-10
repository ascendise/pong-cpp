add_executable(Tests 
"tests.cpp"
"world/world_tests.cpp" 
"world/entity_tests.cpp"
"world/test_doubles/fakes/fake_component.cpp"
"world/test_doubles/fakes/fake_system.cpp"
"rendering/test_doubles/fakes/fake_texture.cpp")

target_link_libraries(Tests PRIVATE PongLib GTest::gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(Tests)