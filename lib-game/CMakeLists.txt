add_library(PongGameLib STATIC
    "src/controls/paddle_player_control.cpp"
)

target_include_directories(PongGameLib PUBLIC 
    "includes/")

target_link_libraries(PongGameLib PUBLIC PongLib)
