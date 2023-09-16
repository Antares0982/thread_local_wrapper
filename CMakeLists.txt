cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ThreadLocalWrapper LANGUAGES CXX)

add_library(common INTERFACE)
if (MSVC)
    # treat no return type as error; ignore anonymous struct/union warning; standard C++20; use multi-thread when compiling
    target_compile_options(common INTERFACE /W4 /we4715 /wd4201 /utf-8 /std:c++20 /MP /Zc:__cplusplus)
else ()
    # no rtti; use pthread; treat no return type as error
    target_compile_options(common INTERFACE -Wall -Wextra -fno-rtti -pthread -Werror=return-type)
endif ()

if (CMAKE_BUILD_TYPE MATCHES ".*Rel.*")
    # use maximal optimization
    message("Release build detected")
    if (MSVC)
        target_compile_options(common INTERFACE /Ox)
    else ()
        target_compile_options(common INTERFACE -O3)
    endif ()
else ()
    message("Debug build detected")
    target_compile_definitions(common INTERFACE TLS_DEBUG)
    if (MSVC)
        # use fast-code optimization
        target_compile_options(common INTERFACE /Ot)
    else ()
        # enabling valgrind memory check
        target_compile_options(common INTERFACE -gdwarf-4)
    endif ()
endif (CMAKE_BUILD_TYPE MATCHES ".*Rel.*")

file(GLOB_RECURSE cpppath src/*.cpp)

if (NOT WIN32)
    target_include_directories(common INTERFACE ./include)
    target_link_options(common INTERFACE -fsanitize=undefined)
    target_link_libraries(common INTERFACE pthread)
else ()
    target_compile_definitions(common INTERFACE NOGDI)
    target_include_directories(common INTERFACE ./include)
    target_link_libraries(common INTERFACE ws2_32)
endif ()

add_subdirectory(cmake_script)

########################################################################################
add_executable(TlsWrap ${cpppath})
target_link_libraries(TlsWrap PRIVATE common)
target_compile_definitions(TlsWrap PRIVATE SELECTION_USE_NEURAL_NETWORK=0)
set_target_properties(TlsWrap PROPERTIES OUTPUT_NAME ReversiGo)
