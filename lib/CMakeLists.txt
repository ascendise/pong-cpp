add_library(PongLib STATIC
    "math.hpp"
    "math.cpp"
    "world/clock.cpp"
    "world/world.hpp"
    "world/entity.cpp"
    "world/world.cpp"
    "rendering/rendering.hpp"
    "rendering/rendering_system.cpp"
    "rendering/texture.cpp" 
    "rendering/sprite.cpp"
    "physics/physics.hpp"  
    "physics/physics_system.cpp" 
    "physics/rigidbody.cpp"
)

target_include_directories(PongLib PUBLIC .)
target_link_libraries(PongLib PRIVATE SDL2::SDL2-static SDL2_image::SDL2_image-static)