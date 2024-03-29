cmake_minimum_required(VERSION 3.20)
project(
		Flibbert
		VERSION 0.1.0
		LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MACOSX_RPATH 1)

find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	# Update submodules as needed
	option(GIT_SUBMODULE "Check submodules during build" ON)
	if (GIT_SUBMODULE)
		message(STATUS "Submodule update")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
				RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if (NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		endif ()
	endif ()
endif ()

include(Dependencies.cmake)

# Project
add_library(Flibbert STATIC
		src/fbtpch.h
		src/Flibbert/Core/Base.h
		src/Flibbert/Core/Application.cpp
		src/Flibbert/Core/Application.h
		src/Flibbert/Core/Camera.cpp
		src/Flibbert/Core/Camera.h
		src/Flibbert/Core/EntryPoint.h
		src/Flibbert/Core/Input.cpp
		src/Flibbert/Core/Input.h
		src/Flibbert/Core/KeyCodes.h
		src/Flibbert/Core/Log.cpp
		src/Flibbert/Core/Log.h
		src/Flibbert/Core/PlatformDetection.h
		src/Platform/OpenGL/Renderer.cpp
		src/Platform/OpenGL/Renderer.h
		src/Platform/OpenGL/VertexArray.cpp
		src/Platform/OpenGL/VertexArray.h
		src/Platform/OpenGL/VertexBuffer.cpp
		src/Platform/OpenGL/VertexBuffer.h
		src/Platform/OpenGL/VertexBufferLayout.h
		src/Platform/OpenGL/IndexBuffer.cpp
		src/Platform/OpenGL/IndexBuffer.h
		src/Platform/OpenGL/Shader.cpp
		src/Platform/OpenGL/Shader.h
		src/Platform/OpenGL/Texture.cpp
		src/Platform/OpenGL/Texture.h)

target_precompile_headers(Flibbert
		PRIVATE src/fbtpch.h)

target_link_libraries(Flibbert
		PUBLIC glad
		PUBLIC glfw
		PUBLIC glm
		PUBLIC imgui
		PUBLIC spdlog
		PUBLIC stb_image)

target_include_directories(Flibbert
		PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
		PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor")

if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(-DDEBUG)
endif ()
