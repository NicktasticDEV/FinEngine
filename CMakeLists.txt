cmake_minimum_required(VERSION 3.25)
project(FinEngine)




# ====================================================================================
# Options
# ====================================================================================
option(FINENGINE_BUILD_EXAMPLES "Build FinEngine example projects" ON)
# ====================================================================================




message(STATUS "")
message(STATUS "========== Configuring FinEngine ==========")




# ====================================================================================
# Source and Header Files
# ====================================================================================

# ========= FinEngine ==========
# Source files
set(FinEngine_SRC
    # Core
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Core/FinGame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Core/FinState.cpp"

    # Platform-agnostic
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/System/System.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Graphics/Graphics.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Windowing/Windowing.cpp"
)
# Header files
set(FinEngine_INCLUDE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# ========== Platform-specific sources =========
# Nintendo Wii
if(CMAKE_SYSTEM_NAME STREQUAL "NintendoWii")
    list(APPEND FinEngine_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/System/Wii/System_Wii.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Graphics/GX/Graphics_GX.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Windowing/Wii/Windowing_Wii.cpp"
    )

# Desktop Platforms
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    list(APPEND FinEngine_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/System/Desktop/System_Desktop.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Graphics/GL/Graphics_GL.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Windowing/Desktop/Windowing_Desktop.cpp"
    )
endif()

# ====================================================================================




# ====================================================================================
# Library Target
# ====================================================================================
add_library(${PROJECT_NAME} ${FinEngine_SRC})
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${FinEngine_INCLUDE}>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
# ====================================================================================




# ====================================================================================
# Defines
# ====================================================================================
# ===== General Desktop Platform =====
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_PLATFORM_DESKTOP
    )
    message(STATUS "Building for: Desktop Platform")
endif()

# ========== Windows Platform ==========
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_PLATFORM_WINDOWS
    )

    # On Windows, export all symbols by default so consumers can link without
    # needing explicit __declspec(dllexport) annotations.
    set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    message(STATUS "Building for: Windows")
endif()

# ========== MacOS Platform ==========
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_PLATFORM_MACOS
    )
    message(STATUS "Building for: macOS")
endif()

# ========== Wii Platform ==========
if (CMAKE_SYSTEM_NAME STREQUAL "NintendoWii")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_PLATFORM_WII # Old name
        PRIVATE FINENGINE_PLATFORM_RVL
    )
    message(STATUS "Building for: Nintendo Wii")
endif()

# ========== Build Type ==========
# Debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_BUILD_TYPE_DEBUG
    )
    message(STATUS "Building config: Debug")

# Release
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_BUILD_TYPE_RELEASE
    )
    message(STATUS "Building config: Relase")
endif()
# ====================================================================================




# ====================================================================================
# Dependencies
# ====================================================================================
# ========== Desktop Dependencies ==========
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_package(OpenGL REQUIRED)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glfw")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glad")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image")

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            glfw
            OpenGL::GL
            Glad
            stb_image
    )
endif()

# ========== Wii Dependencies ==========
if (CMAKE_SYSTEM_NAME STREQUAL "NintendoWii")
    include("${DEVKITPRO}/cmake/Wii.cmake")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image")
    # Include and lib paths for devkitPro
    target_include_directories(${PROJECT_NAME} PRIVATE
        "$ENV{DEVKITPRO}/libogc/include"
        "$ENV{DEVKITPRO}/portlibs/ppc/include"
        "$ENV{DEVKITPRO}/portlibs/wii/include"
    )
    target_link_directories(${PROJECT_NAME} PRIVATE
        "$ENV{DEVKITPRO}/libogc/lib/wii"
        "$ENV{DEVKITPRO}/portlibs/ppc/lib"
        "$ENV{DEVKITPRO}/portlibs/wii/lib"
    )

    target_link_libraries(${PROJECT_NAME} 
        PUBLIC
            ogc
            m
            fat
            bte
            audiogc
            wiiuse
            aesnd
            stb_image
    )
endif()
# ====================================================================================




# ====================================================================================
# location of final artifacts (include platform and build type in path)
# ====================================================================================
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}"
)




# ====================================================================================
# Installation
# ====================================================================================
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    install(TARGETS ${PROJECT_NAME} 
        # TODO: Find a way so that we don't have to add some libraries here kinda like GLFW
        Glad
        stb_image

        EXPORT FinEngineTargets
        RUNTIME DESTINATION bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}
        LIBRARY DESTINATION lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}
        ARCHIVE DESTINATION lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}
    )
else()
    install(TARGETS ${PROJECT_NAME} 
        # TODO: Find a way so that we don't have to add some libraries here kinda like GLFW
        stb_image

        EXPORT FinEngineTargets
        RUNTIME DESTINATION bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}
        LIBRARY DESTINATION lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}
        ARCHIVE DESTINATION lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}
    )
endif()

install(DIRECTORY include/ DESTINATION include)
install(EXPORT FinEngineTargets
    NAMESPACE FinEngine::
    DESTINATION lib/cmake/FinEngine
)
# ====================================================================================




message(STATUS "========== Finished Configuring FinEngine ==========")
message(STATUS "")




# ====================================================================================
# Examples
# ====================================================================================
if(FINENGINE_BUILD_EXAMPLES)
    message(STATUS "Building FinEngine example projects")
    add_subdirectory(examples)
endif()
# ====================================================================================