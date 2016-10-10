cmake_minimum_required(VERSION 2.6)
project(BREAST_CANCER)

set(FANN_BASE "/usr/local/")
find_package(fann REQUIRED)
include_directories( "${FANN_BASE}/include" )
link_directories( "${FANN_BASE}/lib" )

add_executable(breast_cancer data_format.c data_format.h breast_cancer.c)
target_link_libraries(breast_cancer fann)
