cmake_minimum_required(VERSION 2.6)
project(BREAST_CANCER)

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-Wall temp)
if(temp)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()
check_cxx_compiler_flag(-pedantic temp)
if(temp)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
endif()

set(FANN_BASE "/usr/local/")
find_package(fann REQUIRED)
include_directories( "${FANN_BASE}/include" )
link_directories( "${FANN_BASE}/lib" )


add_executable(train_cv_data data_format.c data_format.h train_cv_data.c precision_recall.h precision_recall.c)
target_link_libraries(train_cv_data fann)

add_executable(test_data test_data.c)
target_link_libraries(test_data fann)
