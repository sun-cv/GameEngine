cmake_minimum_required(VERSION 3.12)
project(GameEngine)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP1")

# Include directories for header files directly
set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/engine
    ${CMAKE_SOURCE_DIR}/engine/components
    ${CMAKE_SOURCE_DIR}/engine/components/renderable
    ${CMAKE_SOURCE_DIR}/engine/components/overlay
    ${CMAKE_SOURCE_DIR}/engine/core
    ${CMAKE_SOURCE_DIR}/engine/ecs
    ${CMAKE_SOURCE_DIR}/engine/managers
    ${CMAKE_SOURCE_DIR}/engine/managers/archetype
    ${CMAKE_SOURCE_DIR}/engine/managers/file
    ${CMAKE_SOURCE_DIR}/engine/managers/material
    ${CMAKE_SOURCE_DIR}/engine/managers/mesh
    ${CMAKE_SOURCE_DIR}/engine/managers/prefab
    ${CMAKE_SOURCE_DIR}/engine/managers/shader
    ${CMAKE_SOURCE_DIR}/engine/managers/texture
    ${CMAKE_SOURCE_DIR}/engine/managers/time
    ${CMAKE_SOURCE_DIR}/engine/managers/window
    ${CMAKE_SOURCE_DIR}/engine/systems
    ${CMAKE_SOURCE_DIR}/engine/systems/render
    ${CMAKE_SOURCE_DIR}/engine/systems/interface
    ${CMAKE_SOURCE_DIR}/engine/systems/interface/text
    ${CMAKE_SOURCE_DIR}/engine/systems/interface/text/atlas
    ${CMAKE_SOURCE_DIR}/engine/systems/interface/text/font
    ${CMAKE_SOURCE_DIR}/engine/systems/transform
    ${CMAKE_SOURCE_DIR}/libs
    ${CMAKE_SOURCE_DIR}/libs/glfw/include
    ${CMAKE_SOURCE_DIR}/libs/glad/include
    ${CMAKE_SOURCE_DIR}/libs/nlohmann
    ${CMAKE_SOURCE_DIR}/libs/stb
    ${CMAKE_SOURCE_DIR}/renderer
    ${CMAKE_SOURCE_DIR}/renderer/culling
    ${CMAKE_SOURCE_DIR}/renderer/materials
    ${CMAKE_SOURCE_DIR}/renderer/mesh
    ${CMAKE_SOURCE_DIR}/renderer/shaders
    ${CMAKE_SOURCE_DIR}/renderer/shaders/load
    ${CMAKE_SOURCE_DIR}/renderer/textures
    ${CMAKE_SOURCE_DIR}/utility

)

include_directories(${INCLUDE_DIRECTORIES})

message("Included directories:")
foreach(dir ${INCLUDE_DIRECTORIES})
    message("  ${dir}")
endforeach()

# Find all source files using GLOB_RECURSE
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/**/*.cpp"
)

# Remove any CMake-generated files from the sources list
list(FILTER SOURCES EXCLUDE REGEX ".*CMakeCXXCompilerId.*")


# Add main.cpp and other necessary files to sources if not already included
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/main.cpp")

# Add GLAD and stb_image source files
set(GLAD_SOURCES ${CMAKE_SOURCE_DIR}/libs/glad/src/glad.c)
set(STB_IMAGE_SOURCES ${CMAKE_SOURCE_DIR}/libs/stb/stb_image.cpp)
list(APPEND SOURCES ${GLAD_SOURCES} ${STB_IMAGE_SOURCES})

# Output source files for debugging
message("Source files found:")
foreach(_sourceFile ${SOURCES})
    message("${_sourceFile}")
endforeach()

# Add executable target with all collected sources
add_executable(GameEngine ${SOURCES})

# Link GLFW library
set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib)
target_link_libraries(GameEngine ${GLFW_LIBRARY})

# Windows-specific: Set up OpenGL linking
if(WIN32)
    target_link_libraries(GameEngine opengl32)
endif()

# Fix MSVCRT conflict warning
target_link_options(GameEngine PRIVATE "/NODEFAULTLIB:MSVCRT")
