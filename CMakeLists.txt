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
option(YAL_LOCK "Specifies locking mechanism.")
if(YAL_LOCK STREQUAL "POSIX")
    target_compile_definitions(yal PRIVATE "YAL_LOCK_POSIX")
elseif(YAL_LOCK STREQUAL "FREERTOS")
    target_compile_definitions(yal PRIVATE "YAL_LOCK_FREERTOS")
else()
message(FATAL_ERROR "Locking mechanism is not set. Please specify it from top-level CMake file (example):\n"
    " set(YAL_LOCK POSIX CACHE STRING \"Specifies the locking mechanism used by yal lib\")\n"
    " or from CMake command line option:\n"
    " -DYAL_LOCK=POSIX\n"
    " \n"
    " Available options:\n"
    " POSIX    Use POSIX 'pthread_mutex_t' as locking mechanism.\n"
    " FREERTOS Use FreeRTOS 'SemaphoreHandle_t' as locking mechanism.")
endif()
# } Library

# Examples {
add_executable(slist examples/slist.c)
target_include_directories(slist PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)
target_link_libraries(slist yal)
# } Examples


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