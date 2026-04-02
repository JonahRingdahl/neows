cmake_minimum_required(VERSION 4.2)
project(neows_visualization)

include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3)

FetchContent_Declare(
  curl
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_TAG curl-8_19_0)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.7.1)

FetchContent_MakeAvailable(catch2 raylib curl json)

set(CMAKE_CXX_STANDARD 23)

set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Werror -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(src)

add_executable(Main src/main.cpp 
  src/Engine/engine.cpp
  src/NasaClient/client.cpp
  src/Neos/neo.cpp
)

add_executable(Tests tests/test.cpp src/main.cpp)



target_link_libraries(Main PUBLIC raylib nlohmann_json CURL::libcurl)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain raylib nlohmann_json
  CURL::libcurl)

include(CTest)
include(Catch)
catch_discover_tests(Tests)
