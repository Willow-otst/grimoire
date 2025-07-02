cmake_minimum_required(VERSION 4.0.3)
project(Grimoire)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories("include")

set(EXECUTABLE_OUTPUT_PATH "../bin")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

find_package(Qt6 COMPONENTS Gui Widgets Core REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE fltk)

#target_link_libraries(MyExecutable my_library)
