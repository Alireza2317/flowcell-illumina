cmake_minimum_required(VERSION 3.10)
project(flowcell_illumina VERSION 0.1.0 LANGUAGES CXX)

# For clangd extension
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenCV 4 REQUIRED)

# Define a macro with the path to the project root
add_compile_definitions(PROJECT_ROOT_PATH="${CMAKE_SOURCE_DIR}")

add_library(vision_lib INTERFACE)
target_include_directories(vision_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(vision_lib INTERFACE ${OpenCV_LIBS})

file(GLOB_RECURSE SOURCES "src/*.cpp")


add_executable(datagen src/generate_test_data.cpp)
add_executable(analyze src/run_analysis.cpp)


if(MSVC)
	target_compile_options(datagen PRIVATE /W4)
	target_compile_options(analyze PRIVATE /W4)
else()
	target_compile_options(datagen PRIVATE -Wall -Wextra -Wpedantic)
	target_compile_options(analyze PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(datagen PRIVATE vision_lib)
target_link_libraries(analyze PRIVATE vision_lib)