add_executable(Tests 
"src/tests.cpp"
"src/world/world_tests.cpp" 
"src/world/entity_tests.cpp"
"src/world/events/eventqueue_tests.cpp"
"src/rendering/sprite_tests.cpp" 
"src/vector2d_tests.cpp" 
"src/physics/physics_tests.cpp"
"src/physics/box_collider_tests.cpp"
"src/physics/collision_eventprocessor_tests.cpp"
"src/physics/collision_system_tests.cpp" 
"src/rendering/screen_position_calculator_tests.cpp"
"src/radian_degree_tests.cpp"
"src/test_utility.cpp")

target_include_directories(Tests PRIVATE includes/)

#googletest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
        SYSTEM
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(Tests 
	PRIVATE
	PongLib 
	GTest::gtest_main gmock_main
)

include(GoogleTest)
gtest_discover_tests(Tests)
