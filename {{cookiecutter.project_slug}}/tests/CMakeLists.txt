cmake_minimum_required(VERSION 3.24)

if (NOT BUILD_TESTING)
  message(STATUS "BUILD_TESTING is OFF, skipping tests.")
  return()
endif()

add_executable({{cookiecutter.project_slug}}_tests
  test_main.cpp
)

target_compile_features({{cookiecutter.project_slug}}_tests PRIVATE cxx_std_23)

# Link engine + SDL (if your tests touch SDL/NeneEngine)
target_link_libraries({{cookiecutter.project_slug}}_tests
  PRIVATE
    Nene::Engine
    Nene::SDL3
)

if (MSVC)
  target_compile_options({{cookiecutter.project_slug}}_tests PRIVATE /W4 /permissive-)
else()
  target_compile_options({{cookiecutter.project_slug}}_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Register with CTest
add_test(
  NAME {{cookiecutter.project_slug}}_tests
  COMMAND {{cookiecutter.project_slug}}_tests
)
