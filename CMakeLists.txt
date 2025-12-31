cmake_minimum_required(VERSION 3.15...4.0)
project(ray_tracer VERSION 1.0
        DESCRIPTION "ray tracer from scratch in c++"
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(MACOSX_DEPLOYMENT_TARGET 15.6)
add_library(ray_tracer
  src/img/canvas.cpp
  src/math/matrix.cpp
  src/math/transform.cpp 
  src/geometry/intersection.cpp
  src/geometry/sphere.cpp
  src/math/ray.cpp
  src/math/tuple.cpp
  src/math/util.cpp
  src/lighting/light.cpp
  src/lighting/material.cpp
  src/world/world.cpp
  src/helpers/computation.cpp
  src/camera/camera.cpp
)
target_include_directories(ray_tracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(EMSCRIPTEN)
message(STATUS "compiling with emscripten")
add_executable(first_scene apps/first_scene.cpp)
target_link_libraries(first_scene PRIVATE ray_tracer)

target_compile_options(ray_tracer PRIVATE -O2)
target_link_options(first_scene PRIVATE "-sMODULARIZE=1"
                                    "-sINITIAL_MEMORY=100007936"
                                    "-sEXPORT_NAME=scene_canvas_test"
                                    "-sEXPORTED_RUNTIME_METHODS=['cwrap', 'HEAPU8']"
                                    "-sEXPORTED_FUNCTIONS=['_malloc','_first_scene_render_pixels']")


else()
message(STATUS "compiling without emscripten")
add_executable(plot_projectile apps/plot_projectile.cpp)
target_link_libraries(plot_projectile PRIVATE ray_tracer)
add_executable(clock_face apps/clock_face.cpp)
target_link_libraries(clock_face PRIVATE ray_tracer)
add_executable(draw_circle apps/draw_circle.cpp)
target_link_libraries(draw_circle PRIVATE ray_tracer)
add_executable(draw_shaded_circle apps/draw_shaded_circle.cpp)
target_link_libraries(draw_shaded_circle PRIVATE ray_tracer)
add_executable(first_scene apps/first_scene.cpp)
target_link_libraries(first_scene PRIVATE ray_tracer)


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
    tests/sphere_tests.cpp
    tests/light_tests.cpp
    tests/world_tests.cpp
    tests/camera_tests.cpp
    )
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(unit_tests PRIVATE ray_tracer GTest::gtest_main)


include(GoogleTest)         # helper macros
gtest_discover_tests(unit_tests DISCOVERY_MODE PRE_TEST)  # auto-register tests with CTest

add_executable(misc_tests 
    tests/misc_tests.cpp)
target_include_directories(misc_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(misc_tests PRIVATE ray_tracer GTest::gtest_main)
include(GoogleTest)         # helper macros
gtest_discover_tests(misc_tests DISCOVERY_MODE PRE_TEST)  # auto-register tests with CTest

foreach(t ray_tracer unit_tests plot_projectile misc_tests)
    target_compile_options(${t} PRIVATE
    -Wall -Wextra -Wpedantic
    -Wconversion -Wdouble-promotion -Wfloat-conversion -Wsign-conversion
    )
endforeach()

endif()
