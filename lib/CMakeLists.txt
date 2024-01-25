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

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED)

target_include_directories(PongLib PUBLIC 
    "includes/")

target_link_libraries(PongLib 
	PRIVATE
	SDL2::SDL2
  SDL2_image::SDL2_image
)
