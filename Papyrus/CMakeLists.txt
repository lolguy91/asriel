cmake_minimum_required(VERSION 3.16)

option(BUILD_GLFW "Build the GLFW test" OFF)

set(CMAKE_BUILD_TYPE Release)

project(papyrus-test)

file(GLOB SRC CONFIGURE_DEPENDS "test.c" "src/*.c")

if(BUILD_GLFW)
    list(APPEND SRC "renders/glfw.c" "renders/glad.c")
endif()

add_executable(${PROJECT_NAME} ${SRC})

if(BUILD_GLFW)
    target_link_libraries(${PROJECT_NAME} PRIVATE GL glfw)
else()
    target_link_libraries(${PROJECT_NAME})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE "include" "renders")
