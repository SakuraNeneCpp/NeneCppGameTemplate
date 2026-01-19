cmake_minimum_required(VERSION 3.24)

# NeneEngine as a static library
add_library(NeneEngine STATIC)

target_sources(NeneEngine
  PRIVATE
    src/NeneComponents.cpp
    src/NeneNode.cpp
    src/NeneServer.cpp
    src/NeneUtilities.cpp
)

target_include_directories(NeneEngine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(NeneEngine PUBLIC cxx_std_23)

# If NeneEngine internally uses SDL headers/types, link it here.
# If NeneEngine is SDL-independent, you can remove this.
target_link_libraries(NeneEngine
  PUBLIC
    Nene::SDL3
)

# Useful warnings
if (MSVC)
  target_compile_options(NeneEngine PRIVATE /W4 /permissive-)
else()
  target_compile_options(NeneEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Namespaced alias (nice for external use)
add_library(Nene::Engine ALIAS NeneEngine)
