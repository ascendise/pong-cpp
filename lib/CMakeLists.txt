add_library(PongLib STATIC
    world/world.hpp
    world/entity.cpp
    world/world.cpp)

target_include_directories(PongLib PUBLIC .)