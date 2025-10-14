cmake_minimum_required(VERSION 3.25)
project(FinEngine)
include(cmake/CPM.cmake)

# ==========================================
# Options
# ==========================================
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ==========================================
# Source and Header Files
# ==========================================
set(FinEngine_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Core/FinGame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Graphics/Graphics_Desktop.cpp"
)

set(FinEngine_INCLUDE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# ==========================================
# Library Target
# ==========================================
add_library(${PROJECT_NAME} SHARED ${FinEngine_SRC})
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${FinEngine_INCLUDE}>
        $<INSTALL_INTERFACE:include>
)

# ==========================================
# Dependencies
# ==========================================
# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
CPMAddPackage(
    NAME glfw
    GIT_TAG 3.3-stable
    GITHUB_REPOSITORY glfw/glfw
    OPTIONS 
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_TESTS OFF" 
        "GLFW_BUILD_EXAMPLES OFF" 
        "BUILD_SHARED_LIBS OFF"
)

# Add dependency to the target
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    glfw
    OpenGL::GL
)

# ==========================================
# Installation
# ==========================================
install(TARGETS ${PROJECT_NAME}
    EXPORT FinEngineTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT FinEngineTargets
    NAMESPACE FinEngine::
    DESTINATION lib/cmake/FinEngine
)