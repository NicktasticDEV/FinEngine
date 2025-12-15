cmake_minimum_required(VERSION 3.25)
project(stb_image)

add_library(${PROJECT_NAME} src/stb_image.cpp)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

install(TARGETS ${PROJECT_NAME}
	EXPORT stb_imageTargets
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)