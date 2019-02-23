cmake_minimum_required(VERSION 3.12)
project(untitled2)

find_package(OpenCV)
set(CMAKE_CXX_STANDARD 11)

include_directories(${OpenCV_INCLUDE_DIRS})
# add_executable(untitled2 main.cpp)
add_executable(untitled2 main.cpp cartoon.cpp ImageUtils_0.7.cpp ImageUtils.h)

target_link_libraries(untitled2 ${OpenCV_LIBS})