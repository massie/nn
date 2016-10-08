cmake_minimum_required(VERSION 2.6)
project(OPTDIGITS)

set(FANN_BASE "/usr/local/")
find_package(fann REQUIRED)
include_directories( "${FANN_BASE}/include" )
link_directories( "${FANN_BASE}/lib" )

add_executable(optdigits file_callback.c file_callback.h optdigits.c)
target_link_libraries(optdigits fann)

