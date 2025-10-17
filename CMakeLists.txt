cmake_minimum_required(VERSION 3.22)
project(ray_tracer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_library(ray_tracer
  src/img/canvas.cpp
  src/math/matrix.cpp
  src/math/transform.cpp 
  src/geometry/intersection.cpp
  src/geometry/sphere.cpp
)
target_include_directories(ray_tracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(plot_projectile apps/plot_projectile.cpp)
add_executable(clock_face apps/clock_face.cpp)
target_link_libraries(plot_projectile PRIVATE ray_tracer)
target_link_libraries(clock_face PRIVATE ray_tracer)

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
    tests/matrix_tests.cpp
    tests/transform_tests.cpp
    tests/ray_tests.cpp
    tests/intersection_tests.cpp
    )
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(unit_tests PRIVATE ray_tracer GTest::gtest_main)
include(GoogleTest)         # helper macros
gtest_discover_tests(unit_tests)  # auto-register tests with CTest

add_executable(misc_tests 
    tests/misc_tests.cpp)
target_include_directories(misc_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(misc_tests PRIVATE ray_tracer GTest::gtest_main)
include(GoogleTest)         # helper macros
gtest_discover_tests(misc_tests)  # auto-register tests with CTest

foreach(t ray_tracer unit_tests plot_projectile misc_tests)
    target_compile_options(${t} PRIVATE
    -Wall -Wextra -Wpedantic
    -Wconversion -Wdouble-promotion -Wfloat-conversion -Wsign-conversion
    )
endforeach()