cmake_minimum_required(VERSION 3.22)
project(ray_tracer)
set(CMAKE_CXX_STANDARD 20)
add_library(ray_tracer src/img/canvas.cpp src/math/matrix.cpp)
target_include_directories(ray_tracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(plot_projectile apps/plot_projectile.cpp)
target_link_libraries(plot_projectile PRIVATE ray_tracer)


include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(unit_tests 
    tests/canvas_tests.cpp
    tests/color_tests.cpp
    tests/geo_tests.cpp
    tests/matrix_tests.cpp)
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(unit_tests PRIVATE ray_tracer GTest::gtest_main)
include(GoogleTest)         # helper macros
gtest_discover_tests(unit_tests)  # auto-register tests with CTest

foreach(t ray_tracer unit_tests plot_projectile)
    target_compile_options(${t} PRIVATE -Wall -Wextra -Wpedantic)
endforeach()