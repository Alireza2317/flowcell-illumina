cmake_minimum_required(VERSION 3.10)
project(flowcell_illumina VERSION 0.1.0 LANGUAGES CXX)

# For clangd extension
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenCV 4 REQUIRED)

# Define a macro with the path to the project root
add_compile_definitions(PROJECT_ROOT_PATH="${CMAKE_SOURCE_DIR}")



file(GLOB_RECURSE LIB_SOURCES
"src/analysis/*.cpp"
	"src/data-generation/*.cpp"
	"src/io/*.cpp"
	)


add_library(vision_lib STATIC ${LIB_SOURCES})
target_include_directories(vision_lib PUBLIC include)
target_link_libraries(vision_lib PUBLIC ${OpenCV_LIBS})

add_executable(datagen src/generate_test_data.cpp)
add_executable(analyze src/run_analysis.cpp)


if(MSVC)
	target_compile_options(vision_lib INTERFACE /W4)
else()
	target_compile_options(vision_lib INTERFACE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(datagen PRIVATE vision_lib)
target_link_libraries(analyze PRIVATE vision_lib)