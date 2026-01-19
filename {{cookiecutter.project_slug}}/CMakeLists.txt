cmake_minimum_required(VERSION 3.24)

project({{cookiecutter.project_slug}}
  VERSION 0.1.0
  LANGUAGES CXX
)

# -----------------------------
# Global settings
# -----------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output dirs (nice for Windows)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Enable testing via CTest
include(CTest)

# -----------------------------
# Options
# -----------------------------
option(NENE_USE_SYSTEM_SDL3 "Use SDL3 from the system (find_package) instead of FetchContent" ON)
option(NENE_BUILD_TESTS "Build tests" ON)

# -----------------------------
# SDL3
# -----------------------------
if (NENE_USE_SYSTEM_SDL3)
  # You should have SDL3 installed with CMake config packages.
  # Typical: vcpkg install sdl3
  find_package(SDL3 CONFIG REQUIRED)
else()
  include(FetchContent)
  FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.0
  )
  FetchContent_MakeAvailable(SDL3)
endif()

# SDL3::SDL3 is usually provided by SDL3 CONFIG.
# If you are using FetchContent, the target may be SDL3::SDL3 or SDL3.
# Let's normalize it into an alias target called "Nene::SDL3".
if (TARGET SDL3::SDL3)
  add_library(Nene::SDL3 ALIAS SDL3::SDL3)
elseif(TARGET SDL3)
  add_library(Nene::SDL3 ALIAS SDL3)
else()
  message(FATAL_ERROR "SDL3 target not found. Expected SDL3::SDL3 or SDL3.")
endif()

# -----------------------------
# Subprojects
# -----------------------------
add_subdirectory(NeneEngine)
add_subdirectory(src)

if (NENE_BUILD_TESTS AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
