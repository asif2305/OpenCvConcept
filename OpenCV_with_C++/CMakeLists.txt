cmake_minimum_required(VERSION 3.0.0)
project(OPENCV_WITH_C++ VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OPENCV_WITH_C++ main.cpp)

target_link_libraries(OPENCV_WITH_C++ ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
