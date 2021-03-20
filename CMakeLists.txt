cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME "My_trial_project")
set(EXECUTABLE_NAME "My_trial_project")

set(CMAKE_CXX_STANDART 17)

project(${PROJECT_NAME})

add_executable(${EXECUTABLE_NAME} src/main.cpp 
                                  src/Renderer/ShaderProgram.h 
                                  src/Renderer/ShaderProgram.cpp)
								  
##add_executable(${EXECUTABLE_NAME} src/main2.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

##add_subdirectory(external/glew)
##target_link_libraries(${PROJECT_NAME} glew)