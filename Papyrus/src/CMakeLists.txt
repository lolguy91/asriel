cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Release)

project(papyrus)

IF(WIN32)
    set(CMAKE_CXX_FLAGS "/EHsc /std:c++20")
ELSEIF(CMAKE_HOST_SYSTEM_NAME MATCHES OpenBSD)
    set(CMAKE_CXX_FLAGS "-I /usr/local/include -I /usr/X11R6/include -L /usr/local/lib -L /usr/X11R6/lib -std=c++20 -g")
ELSEIF(CMAKE_HOST_SYSTEM_NAME MATCHES FreeBSD)
    set(CMAKE_CXX_FLAGS "-I /usr/local/include -L /usr/local/lib -std=c++20 -g")
ELSEIF(CMAKE_HOST_SYSTEM_NAME MATCHES NetBSD)
    set(CMAKE_CXX_FLAGS "-I /usr/pkg/include -I /usr/X11R7/include -L /usr/pkg/lib -L /usr/X11R7/lib -std=c++20 -Wall -Wextra -g")
ELSE()
    set(CMAKE_CXX_FLAGS "-std=c++20 -g")
ENDIF()

file(GLOB SRC CONFIGURE_DEPENDS "*.h" "*.c")

IF(WIN32)
    add_library(${PROJECT_NAME} STATIC ${SRC})
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 glfw3)
    target_include_directories(${PROJECT_NAME} PRIVATE "../include")
ELSE()
    add_library(${PROJECT_NAME} STATIC ${SRC})
    target_link_libraries(${PROJECT_NAME} GL glfw)
    target_include_directories(${PROJECT_NAME} PRIVATE "../include")
ENDIF()

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES "../include/papyrus.h" DESTINATION include)
