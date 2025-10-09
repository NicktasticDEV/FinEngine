cmake_minimum_required(VERSION 3.25)
project(FinEngine)

set(FinEngine_SRC

)

set(FinEngine_INCLUDE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_library(${PROJECT_NAME} ${FinEngine_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${FinEngine_INCLUDE})