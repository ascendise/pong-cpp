add_executable(Pong main.cpp)

if (WIN32)
    add_custom_command(
        TARGET Pong POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:Pong>"
        VERBATIM
    )
endif()

target_link_libraries(Pong PRIVATE PongLib SDL2::SDL2-static SDL2main SDL2_image::SDL2_image-static)