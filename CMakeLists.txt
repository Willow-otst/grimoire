cmake_minimum_required(VERSION 4.0.3)
project(Grimoire)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories("include")

set(EXECUTABLE_OUTPUT_PATH "../bin")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

find_package(wxWidgets REQUIRED COMPONENTS core base richtext)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
target_link_libraries(${CMAKE_PROJECT_NAME} ${wxWidgets_LIBRARIES})

include_directories("lib/TOML")
