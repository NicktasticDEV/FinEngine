cmake_minimum_required(VERSION 3.25)
project(Glad)

add_library(${PROJECT_NAME} src/glad.c)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

install(TARGETS ${PROJECT_NAME}
	EXPORT GladTargets
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)