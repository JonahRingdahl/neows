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

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master)

FetchContent_MakeAvailable(raylib cpp-httplib json)

set(CMAKE_CXX_STANDARD 23)

set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Werror -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(src)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(Main ${SOURCES})

add_executable(Tests ${SOURCES})

target_link_libraries(Main PUBLIC raylib nlohmann_json httplib)
target_link_libraries(Tests PRIVATE raylib nlohmann_json
                                    httplib)
