add_library(PongLib STATIC
    "src/math.cpp"
    "src/world/clock.cpp"
    "src/world/entity.cpp"
    "src/world/world.cpp"
    "src/world/events/events.cpp"
    "src/rendering/rendering_system.cpp"
    "src/rendering/texture.cpp" 
    "src/rendering/sprite.cpp"
    "src/rendering/screen_position_calculator.cpp"
    "src/physics/movement_system.cpp" 
    "src/physics/rigidbody.cpp"
    "src/physics/box_collider.cpp"
    "src/physics/collision_event.cpp"
    "src/physics/collision_eventprocessor.cpp"
    "src/physics/collision_system.cpp")

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2 SDL2main)
find_package(SDL2_image)

if(${SDL2_image_FOUND})
	target_link_libraries(PongLib PRIVATE SDL2_image::SDL2_image)
else()
	#In case package manager only finds older version of SDL2_image that does
	#not include a cmake.config (for example the Github Ubuntu Workflow Runner...)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(SDL2_image REQUIRED SDL2_image)
	target_link_libraries(PongLib PRIVATE ${SDL2_image_LIBRARIES})
	target_include_directories(PongLib PRIVATE ${SDL2_image_INCLUDE_DIRS})
	target_compile_options(PongLib PRIVATE ${SDL2_image_CFLAGS_OTHER})
endif()

target_include_directories(PongLib PUBLIC 
    "includes/")

target_link_libraries(PongLib 
	PRIVATE
	SDL2::SDL2
)
