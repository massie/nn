cmake_minimum_required(VERSION 2.6)
project(OPTDIGITS)

set(FANN_BASE "/usr/local/")
find_package(fann REQUIRED)
include_directories( "${FANN_BASE}/include" )
link_directories( "${FANN_BASE}/lib" )

add_executable(optdigits optdigits.c)
target_link_libraries(optdigits fann)

