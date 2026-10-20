cmake_minimum_required(VERSION 3.16)
project(Frogger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use an installed raylib if found, otherwise download and build it.
find_package(raylib 5.0 QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(raylib)
endif()

file(GLOB_RECURSE FROGGER_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(frogger ${FROGGER_SOURCES} "src/entities/Turtle.h" "src/entities/Turtle.cpp" "src/lanes/TurtleLane.h" "src/lanes/TurtleLane.cpp" "src/states/OptionsState.h" "src/states/OptionsState.cpp" "src/world/TileUtils.h" "src/core/CatalogCheck.h" "src/core/SoundCatalog.h" "src/core/TextureCatalog.h")
target_include_directories(frogger PRIVATE src)
target_link_libraries(frogger PRIVATE raylib)

# Copy the resources folder next to the executable (if you have one).
if (EXISTS ${CMAKE_SOURCE_DIR}/resources)
    add_custom_command(TARGET frogger POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:frogger>/resources)
endif()
