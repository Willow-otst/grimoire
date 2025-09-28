cmake_minimum_required(VERSION 4.0.3)
project(Grimoire)

set(CMAKE_CXX_STANDARD 20)

# === Source Files ===
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")
include_directories("include")

# === SQLite with FTS5 ===
file(GLOB_RECURSE SQLITE_SOURCES "lib/sqlite/src/*.c")
add_library(sqlite3 STATIC ${SQLITE_SOURCES})
target_include_directories(sqlite3 PRIVATE "lib/sqlite/include")
target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_FTS5)

# === TOML ===
include_directories("lib/TOML")

# === stduuid ===
include_directories("lib/stduuid/include")

# === Executable ===
set(EXECUTABLE_OUTPUT_PATH "../bin")
add_executable(${PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sqlite3)

# === wxWidgets ===
find_package(wxWidgets REQUIRED COMPONENTS core base richtext)
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})
