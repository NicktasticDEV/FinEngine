cmake_minimum_required(VERSION 3.25)
project(Simple)

add_executable(${PROJECT_NAME}
    "src/main.cpp"
    "src/States/TestState.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "src"
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        FinEngine
)

if (CMAKE_SYSTEM_NAME STREQUAL "NintendoWii")
    include("${DEVKITPRO}/cmake/Wii.cmake")
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
endif()