cmake_minimum_required(VERSION 3.25)
project(FinEngine)
include(cmake/CPM.cmake)

# ==========================================
# Source and Header Files
# ==========================================

# ===== Core sources =====
set(FinEngine_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Core/FinGame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Core/FinBasic.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/System/System.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Graphics/Graphics.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Audio/Audio.cpp"
)

# ===== Platform-specific sources =====
# Nintendo Wii
if(CMAKE_SYSTEM_NAME STREQUAL "NintendoWii")
    list(APPEND FinEngine_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/System/Wii/System_Wii.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Graphics/GX/Graphics_GX.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FinEngine/Platform/Audio/Wii/Audio_Wii.cpp"
    )
endif()

# ===== Include directories =====
set(FinEngine_INCLUDE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# ==========================================
# Options
# ==========================================
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ==========================================
# Library Target
# ==========================================
add_library(${PROJECT_NAME} ${FinEngine_SRC})
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${FinEngine_INCLUDE}>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# ==========================================
# Defines
# ==========================================

# Windows Platform
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_PLATFORM_WINDOWS
    )

    # On Windows, export all symbols by default so consumers can link without
    # needing explicit __declspec(dllexport) annotations.
    set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    message(STATUS "Building for Windows platform")
endif()

# MacOS Platform
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_PLATFORM_MACOS
    )
    message(STATUS "Building for macOS platform")
endif()

# Desktop Platform (Windows, Linux, macOS)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_PLATFORM_DESKTOP
    )
    message(STATUS "Building for Desktop platform")
endif()

# Wii Platform
if (CMAKE_SYSTEM_NAME STREQUAL "NintendoWii")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE FINENGINE_PLATFORM_WII
    )
    message(STATUS "Building for Nintendo Wii platform")
endif()

# ==========================================
# Dependencies
# ==========================================

# Wii Dependencies
if (CMAKE_SYSTEM_NAME STREQUAL "NintendoWii")
    message(STATUS "Configuring dependencies for Nintendo Wii platform")
    include("${DEVKITPRO}/cmake/Wii.cmake")
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
        ogc
        m
        fat
        bte
        audiogc
        wiiuse
        aesnd
    )
endif()

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
