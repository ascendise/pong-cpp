add_library(PongLib STATIC
    "math.hpp"
    "math.cpp"
    "world/clock.cpp"
    "world/world.hpp"
    "world/entity.cpp"
    "world/world.cpp"
    "world/events/events.hpp"
    "world/events/events.cpp"
    "rendering/rendering.hpp"
    "rendering/rendering_system.cpp"
    "rendering/texture.cpp" 
    "rendering/sprite.cpp"
    "rendering/utils.hpp"
    "rendering/surface.cpp"
    "rendering/screen_position_calculator.cpp"
    "physics/physics.hpp"  
    "physics/physics_system.cpp" 
    "physics/rigidbody.cpp"
    "physics/box_collider.cpp"
    "physics/collision_event.cpp"
    "physics/collision_eventprocessor.cpp"
    "physics/collision_system.cpp")

target_include_directories(PongLib PUBLIC .)
target_link_libraries(PongLib PRIVATE SDL2::SDL2-static SDL2_image::SDL2_image-static)