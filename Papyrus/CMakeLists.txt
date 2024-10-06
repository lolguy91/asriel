cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Release)

project(papyrus-test)

file(GLOB SRC CONFIGURE_DEPENDS "test.c" "src/*.c" "renders/*.c")

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE GL glfw)
target_include_directories(${PROJECT_NAME} PRIVATE "renders")
