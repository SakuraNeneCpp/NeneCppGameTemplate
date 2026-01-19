cmake_minimum_required(VERSION 3.24)

# Main game executable
add_executable({{cookiecutter.project_slug}}
  main.cpp
  game.cpp
)

target_compile_features({{cookiecutter.project_slug}} PRIVATE cxx_std_23)

# Your game uses both NeneEngine and SDL3
target_link_libraries({{cookiecutter.project_slug}}
  PRIVATE
    Nene::Engine
    Nene::SDL3
)

# Assets directory path as a compile-time definition (optional but useful)
# Use in code: std::string assetRoot = NENE_ASSET_DIR;
target_compile_definitions({{cookiecutter.project_slug}}
  PRIVATE
    NENE_ASSET_DIR="${CMAKE_SOURCE_DIR}/assets"
)

# Nice warnings
if (MSVC)
  target_compile_options({{cookiecutter.project_slug}} PRIVATE /W4 /permissive-)
else()
  target_compile_options({{cookiecutter.project_slug}} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# On Windows, copy SDL DLL next to executable if needed
# (Mostly required when using system-installed SDL3 shared libs.)
if (WIN32)
  add_custom_command(TARGET {{cookiecutter.project_slug}} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Post-build step done."
  )
endif()
