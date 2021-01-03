cmake_minimum_required (VERSION 2.8)
cmake_policy(VERSION 2.8)

project (Oniris)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)

link_directories(${CMAKE_SOURCE_DIR}/lib)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")
find_package(IRRKLANG REQUIRED)
message(STATUS "Found IRRKLANG in ${IRRKLANG_INCLUDE_DIR}")
# find_package(GLEW REQUIRED)
# message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")

add_library(GLAD "thirdparty/glad.c")

if(WIN32)
  set(LIBS glfw3 opengl32 assimp irrKlang)
elseif(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  find_package(OpenGL REQUIRED)
  add_definitions(${OPENGL_DEFINITIONS})
  find_package(X11 REQUIRED)
  # note that the order is important for setting the libs
  # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
  set(LIBS ${GLFW3_LIBRARY} ${IRRKLANG_LIBRARIES} X11 Xrandr Xinerama Xi Xcursor GL dl pthread ${ASSIMP_LIBRARY})
  set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
elseif(APPLE)
  INCLUDE_DIRECTORIES(/System/Library/Frameworks)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  FIND_LIBRARY(IOKit_LIBRARY IOKit)
  FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
  MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
  SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
  SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY})
  set(LIBS ${LIBS} ${APPLE_LIBS})
else()
  set(LIBS )
endif(WIN32)

add_library(STB_IMAGE "thirdparty/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

set(LIBS ${LIBS} GLAD)

macro(makeLink src dest target)
  add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}  DEPENDS  ${dest} COMMENT "mklink ${src} -> ${dest}")
endmacro()

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# Configure assets header file
configure_file(src/helpers/RootDir.h src/helpers/RootDir.h)
include_directories(
  ${CMAKE_BINARY_DIR}/src
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

# RESOURCES
# Add Shaders
file(GLOB_RECURSE RES_FILES *.frag *.vert *.glsl *.shader)
# Add Textures
file(COPY ${CMAKE_SOURCE_DIR}/res/img/
	DESTINATION ${CMAKE_BINARY_DIR}/res/img)
# Add Models
file(COPY ${CMAKE_SOURCE_DIR}/res/models/
	DESTINATION ${CMAKE_BINARY_DIR}/res/models)
# Add Audios
file(COPY ${CMAKE_SOURCE_DIR}/res/audio/
	DESTINATION ${CMAKE_BINARY_DIR}/res/audio)
# Add Scene files
file(COPY ${CMAKE_SOURCE_DIR}/res/scene/
	DESTINATION ${CMAKE_BINARY_DIR}/res/scene)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${RES_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBS})
if(WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
  set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug")
elseif(UNIX AND NOT APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
elseif(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
endif(WIN32)

# copy shader files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/res/shaders/
  DESTINATION ${CMAKE_BINARY_DIR}/res/shaders)
  
# copy ipkMP3 into build folder
file(COPY ${CMAKE_SOURCE_DIR}/lib/ikpMP3.so
DESTINATION ${CMAKE_SOURCE_DIR}/build)

#include_directories(${CMAKE_SOURCE_DIR}/include)