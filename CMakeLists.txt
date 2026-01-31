cmake_minimum_required(VERSION 4.2)
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

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.7.1)

FetchContent_MakeAvailable(catch2 raylib cpp-httplib json)

set(CMAKE_CXX_STANDARD 23)

set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Werror -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(src)

add_executable(Main src/main.cpp 
		    src/Neo/Neo.cpp src/Neo/Diameter.cpp
                    src/Neo/CloseApproach.cpp src/Neo/NeosCurrier.cpp
                    src/Menu/Menu.cpp
		    src/utils/NasaAPI/api.cpp)

add_executable(Tests tests/test.cpp 
	  	    src/Neo/Neo.cpp src/Neo/Diameter.cpp
                    src/Neo/CloseApproach.cpp src/Neo/NeosCurrier.cpp
                    src/Menu/Menu.cpp
		    src/utils/NasaAPI/api.cpp)



target_link_libraries(Main PUBLIC raylib nlohmann_json httplib)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain raylib nlohmann_json
                                    httplib)

include(CTest)
include(Catch)
catch_discover_tests(Tests)
