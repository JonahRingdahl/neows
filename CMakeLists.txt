cmake_minimum_required(VERSION 3.30)
project(neows_visualization)

include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3)

FetchContent_Declare(
  cpp-httplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
  GIT_TAG v0.18.1)

set(HTTPLIB_REQUIRE_OPENSSL ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0)

set(CLAY_INCLUDE_ALL_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  clay
  GIT_REPOSITORY https://github.com/nicbarker/clay.git
  GIT_TAG main)

FetchContent_MakeAvailable(raylib cpp-httplib json catch2 clay)

set(CMAKE_CXX_STANDARD 23)

set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Werror -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(src)
include_directories(${clay_SOURCE_DIR} ${clay_SOURCE_DIR}/renderers/raylib)

file(GLOB_RECURSE SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_executable(Main src/main.cpp ${SOURCES})

add_executable(Tests ${SOURCES})

target_link_libraries(Main PUBLIC raylib nlohmann_json httplib)
target_link_libraries(Tests PRIVATE raylib nlohmann_json
                                    httplib Catch2::Catch2WithMain)
