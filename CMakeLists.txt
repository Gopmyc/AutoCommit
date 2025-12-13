cmake_minimum_required(VERSION 3.15)
project(AutoCommit C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

include_directories(${PROJECT_SOURCE_DIR}/includes)

file(GLOB SRC "srcs/*.c" "libraries/cJSON/*.c")

set(EXECUTABLE_NAME auto_commit)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/builds")

if(WIN32)
    set(ICON_RC ${PROJECT_SOURCE_DIR}/builds/icon.rc)
    enable_language(RC)
    add_executable(${EXECUTABLE_NAME} ${SRC} ${ICON_RC})
else()
    add_executable(${EXECUTABLE_NAME} ${SRC})
endif()
