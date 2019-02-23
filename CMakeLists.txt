cmake_minimum_required(VERSION 3.12)
project(opencv_example)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

#include_directories(/usr/local/Cellar/opencv/4.0.1/include/opencv4)

add_executable(opencv_example main.cpp)

target_link_libraries(opencv_example ${OpenCV_LIBS})
#target_link_libraries(opencv_example '/usr/local/Cellar/opencv/4.0.1/lib')