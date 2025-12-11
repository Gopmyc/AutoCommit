cmake_minimum_required(VERSION 3.15)
project(AutoCommit C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Inclure les headers
include_directories(${PROJECT_SOURCE_DIR}/includes)

# Sources
file(GLOB SRC "srcs/*.c" "libraries/cJSON/*.c")

# Binaire
set(BIN ${PROJECT_SOURCE_DIR}/builds/auto_commit)

# Détecter Windows pour l’icône
if(WIN32)
    set(ICON_RC ${PROJECT_SOURCE_DIR}/builds/icon.rc)
    enable_language(RC)
    add_executable(${BIN} ${SRC} ${ICON_RC})
else()
    add_executable(${BIN} ${SRC})
endif()