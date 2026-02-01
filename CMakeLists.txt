cmake_minimum_required(VERSION 3.26)

project(APP
	VERSION 0.1
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(APP)

target_sources(APP
	PRIVATE 
		src/main.cpp
		src/test.cpp
)

target_include_directories(APP
	PRIVATE 
		include
)