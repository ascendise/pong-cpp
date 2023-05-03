add_library(PongLib STATIC
    world/world.hpp
    world/entity.cpp
    world/world.cpp
    rendering/rendering.hpp
    rendering/rendering_system.cpp)

target_include_directories(PongLib PUBLIC .)
target_link_libraries(PongLib PRIVATE SDL2::SDL2-static SDL2_image::SDL2_image-static)