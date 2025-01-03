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
    ${CMAKE_SOURCE_DIR}/engine/controller
    ${CMAKE_SOURCE_DIR}/engine/controller/input
    ${CMAKE_SOURCE_DIR}/engine/controller/window
    ${CMAKE_SOURCE_DIR}/engine/controller/window
    ${CMAKE_SOURCE_DIR}/engine/core
    ${CMAKE_SOURCE_DIR}/engine/ecs
    ${CMAKE_SOURCE_DIR}/engine/ecs/component
    ${CMAKE_SOURCE_DIR}/engine/ecs/entity
    ${CMAKE_SOURCE_DIR}/engine/ecs/entity/factory
    ${CMAKE_SOURCE_DIR}/engine/include
    ${CMAKE_SOURCE_DIR}/engine/include/forward
    ${CMAKE_SOURCE_DIR}/engine/system
    ${CMAKE_SOURCE_DIR}/engine/system/asset
    ${CMAKE_SOURCE_DIR}/engine/system/asset/material
    ${CMAKE_SOURCE_DIR}/engine/system/asset/mesh
    ${CMAKE_SOURCE_DIR}/engine/system/asset/texture
    ${CMAKE_SOURCE_DIR}/engine/system/event
    ${CMAKE_SOURCE_DIR}/engine/system/render
    ${CMAKE_SOURCE_DIR}/engine/system/render/renderer
    ${CMAKE_SOURCE_DIR}/engine/system/render/shader
    ${CMAKE_SOURCE_DIR}/engine/system/render/src
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/libs
    ${CMAKE_SOURCE_DIR}/libs/glfw/include
    ${CMAKE_SOURCE_DIR}/libs/glad/include
    ${CMAKE_SOURCE_DIR}/libs/glm
    ${CMAKE_SOURCE_DIR}/libs/imgui
    ${CMAKE_SOURCE_DIR}/libs/nlohmann
    ${CMAKE_SOURCE_DIR}/libs/stb
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/util
    ${CMAKE_SOURCE_DIR}/util/class
    ${CMAKE_SOURCE_DIR}/util/debug
    ${CMAKE_SOURCE_DIR}/util/debug/test
    ${CMAKE_SOURCE_DIR}/util/error
    ${CMAKE_SOURCE_DIR}/util/log
    ${CMAKE_SOURCE_DIR}/util/toolkit
    ${CMAKE_SOURCE_DIR}/util/toolkit/file

    ${CMAKE_SOURCE_DIR}
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
