cmake_minimum_required(VERSION 3.24)
project(disp2Depth)

set(CMAKE_CXX_STANDARD 17)
include_directories("/usr/include/eigen3")

find_package(OpenCV 3 REQUIRED)
find_package(Pangolin REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS}})
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(disp2Depth main.cpp)

target_link_libraries(disp2Depth ${OpenCV_LIBRARIES} ${Pangolin_LIBRARIES})