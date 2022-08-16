cmake_minimum_required(VERSION 3.16)
project("TPSX")

set(BUILD_MODE "DEBUG")

if (NOT MSVC)
    if (BUILD_MODE EQUAL "RELEASE")
        # BASICALLY RELEASE MODE
        SET(CMAKE_C_FLAGS  "-m64 -Ofast -flto -march=native")
    elseif(BUILD_MODE EQUAL "DEBUG")
        # DEBUG MODE
        SET(CMAKE_C_FLAGS "-g -ggdb -fsanitize=address")
        SET(CMAKE_C_FLAGS "-g -Werror -Wall -Wextra")
        SET(CMAKE_C_FLAGS "-O0 -g -D _DEBUG")
    endif()
endif()

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(FindPkgConfig)
find_package(SDL2 REQUIRED)

include_directories(vendor/stb/)
include_directories(vendor/Tlib/)
include_directories(src/)

file(GLOB_RECURSE "TPSX_code" SRC src/*.c)
add_library(TPSX STATIC ${TPSX_code})

target_link_libraries(TPSX LINK_PRIVATE "${SDL2_LIBRARIES}")
if (NOT MSVC)
    target_link_libraries(TPSX LINK_PRIVATE m)
endif()

include_directories("${SDL2_INCLUDE_DIRS}")

include_directories(src/demo)
file(GLOB_RECURSE "TPSX_demo_code" SRC demo/*.c)
add_executable(demo WIN32 ${TPSX_demo_code})
target_link_libraries(demo LINK_PRIVATE TPSX)
