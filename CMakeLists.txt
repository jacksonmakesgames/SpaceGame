cmake_minimum_required (VERSION 3.15)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_STANDARD 			17)
set(CMAKE_CXX_EXTENSIONS 		OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT 				${CMAKE_SOURCE_DIR}/../../../Watty)
set(WATTYVERSION 				0.31.0)
set(CORE 				Watty-Core)
set(LIBNAME 			Watty_v${WATTYVERSION})
set(WATTYDIR 			${ROOT})
set(COREDIR 			${WATTYDIR}/${CORE})

set(CMAKE_CONFIGURATION_TYPES 		Debug Release Web)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

add_compile_definitions(FT2_BUILD_LIBRARY)
add_compile_definitions(GL_WITH_GLAD) # for freetype


include(${ROOT}/tools/functions.cmake)
create_resources("${CMAKE_CURRENT_SOURCE_DIR}/res" OFF)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/res")


project(Resources)
	file(GLOB_RECURSE RES_INPUTS 		"*/res.cpp")
	file(GLOB_RECURSE RES_HEADER 		"*/res.h")
	add_library(Resources OBJECT
		${RES_HEADER}
		${RES_INPUTS}
	)


include_directories(
	${COREDIR}/
	${COREDIR}/include/
	${COREDIR}/include/Watty
	${WATTYDIR}/dependencies/stb
	${WATTYDIR}/dependencies/glad/include
	${WATTYDIR}/dependencies/glfw/include
	${WATTYDIR}/dependencies/freetype/include
	${WATTYDIR}/dependencies/freetype-gl
	${WATTYDIR}/dependencies/box2d/Box2D_v2.3.1
	${WATTYDIR}/dependencies/soloud/include
	${WATTYDIR}/dependencies/json/include
	${WATTYDIR}/dependencies/glm/include
	${WATTYDIR}/dependencies/imgui
	${WATTYDIR}/dependencies/imgui/examples
) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
link_libraries(${LIBNAME})
link_libraries($<TARGET_OBJECTS:Resources>)

add_compile_definitions(WATTY_OPENGL)
project (Space)
include_directories(include)
file(GLOB_RECURSE SOURCES "src/**.cpp")
file(GLOB_RECURSE HEADERS "**.h")
add_executable(Space ${SOURCES} ${HEADERS} )

