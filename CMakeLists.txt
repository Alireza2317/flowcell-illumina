cmake_minimum_required(VERSION 3.10)
project(flowcell_illumina VERSION 0.1.0 LANGUAGES CXX)

# For clangd extension
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenCV 4 REQUIRED)

# Define a macro with the path to the project root
add_definitions(-DPROJECT_ROOT_PATH="${CMAKE_SOURCE_DIR}")

add_library(vision_lib INTERFACE)
target_include_directories(vision_lib INTERFACE include)
target_link_libraries(vision_lib INTERFACE ${OpenCV_LIBS})


add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE vision_lib ${OpenCV_LIBS})