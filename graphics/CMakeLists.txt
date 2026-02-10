add_library(graphics STATIC
	src/shader_program.cpp
)

target_include_directories(graphics
	PUBLIC
		include
)

find_package(OpenGL REQUIRED)

target_link_libraries(graphics
	PUBLIC
		glad
		OpenGL::GL
		debug_utils
)