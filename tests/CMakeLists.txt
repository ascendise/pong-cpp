add_executable(Tests 
"tests.cpp"
"world/world_tests.cpp" 
"world/entity_tests.cpp"
"world/events/eventqueue_tests.cpp"
"world/events/fake_event.cpp"
"world/events/fake_eventprocessor.cpp"
"world/events/spy_eventqueueport.cpp"
"world/test_doubles/fakes/fake_component.cpp"
"world/test_doubles/fakes/fake_system.cpp"
"rendering/test_doubles/fakes/fake_texture.cpp"
"rendering/sprite_tests.cpp" 
"vector2d_tests.cpp" 
"physics/physics_tests.cpp"
"physics/box_collider_tests.cpp"
"physics/test_doubles/stub/clock_stub.cpp"
"physics/collision_eventprocessor_tests.cpp"
"physics/collision_system_tests.cpp" 
"rendering/test_doubles/fakes/fake_surface.cpp" 
"rendering/screen_position_calculator_tests.cpp"
"radian_degree_tests.cpp"
"test_utility.hpp"
"test_utility.cpp")

target_link_libraries(Tests 
	PRIVATE PongLib 
	SDL2::SDL2-static 
	SDL2_image::SDL2_image-static 
	GTest::gtest_main gmock_main
)

include(GoogleTest)
gtest_discover_tests(Tests)
