cmake_minimum_required(VERSION 3.27.4)
set(CMAKE_C_STANDARD 99)
project(yal_proj)

# Library {
add_library(yal STATIC src/single_list.c)
# target_sources(yal PRIVATE
#     src/single_list.c
# )
target_include_directories(yal PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)
option(YAL_THREAD "Specifies locking mechanism.")
# } Library

# Examples {
add_executable(slist examples/slist.c)
target_include_directories(slist PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)
target_link_libraries(slist yal)
# } Examples

# Common {
if(YAL_THREAD STREQUAL "POSIX")
    target_compile_definitions(yal PRIVATE "YAL_THREAD_POSIX")
    target_compile_definitions(slist PRIVATE "YAL_THREAD_POSIX")
elseif(YAL_THREAD STREQUAL "FREERTOS")
    target_compile_definitions(yal PRIVATE "YAL_THREAD_FREERTOS")
    target_compile_definitions(slist PRIVATE "YAL_THREAD_FREERTOS")
elseif(YAL_THREAD STREQUAL "MSVC")
    target_compile_definitions(yal PRIVATE "YAL_THREAD_MSVC")
    target_compile_definitions(slist PRIVATE "YAL_THREAD_MSVC")
elseif(YAL_THREAD STREQUAL "NONE")
    target_compile_definitions(yal PRIVATE "YAL_THREAD_NONE")
    target_compile_definitions(slist PRIVATE "YAL_THREAD_NONE")
else()
    message(FATAL_ERROR "Locking mechanism is not set. Please specify it from top-level CMake file (example):\n"
    " set(YAL_THREAD POSIX CACHE STRING \"Specifies the locking mechanism used by yal lib\")\n"
    " or from CMake command line option:\n"
    " -DYAL_THREAD=POSIX\n"
    " \n"
    " Available options:\n"
    " POSIX    Use POSIX 'pthread_mutex_t' as locking mechanism.\n"
    " FREERTOS Use FreeRTOS 'SemaphoreHandle_t' as locking mechanism.\n"
    " MSVC     Use MSVC 'HANDLE' (CreateMutex) as locking mechanism.\n"
    " NONE     Don't use any locking mechanism.")
endif()
# } Common

# add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/..")
# 
# target_include_directories(slist PUBLIC
#     "${CMAKE_CURRENT_SOURCE_DIR}/../inc"
# )
# 
# 
# cmake_minimum_required(VERSION 3.27.4)
# set(CMAKE_C_STANDARD 99)
# project(yal)
# add_library(yal STATIC)
# 
# target_sources(yal PRIVATE
#     src/single_list.c
# )
# add_executable(slist slist.c)