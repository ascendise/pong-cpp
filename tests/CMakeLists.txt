add_executable(Tests 
"tests.cpp"
"world/world_tests.cpp" 
"world/entity_tests.cpp"
"world/test_doubles/fakes/fake_component.cpp"
"world/test_doubles/fakes/fake_system.cpp"
"rendering/test_doubles/fakes/fake_texture.cpp"
"rendering/sprite_tests.cpp")

target_link_libraries(Tests PRIVATE PongLib SDL2::SDL2-static SDL2_image::SDL2_image-static GTest::gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(Tests)