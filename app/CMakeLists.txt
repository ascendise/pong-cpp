add_executable(Pong 
	"src/prefabs.cpp"
    "src/main.cpp")

target_include_directories(Pong PRIVATE includes/)

find_package(SDL2 REQUIRED CONFIG)

target_link_libraries(Pong 
	PRIVATE
	PongGameLib
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
