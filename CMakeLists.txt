cmake_minimum_required(VERSION 3.0)

project(recognition)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic)

find_package(Python3 COMPONENTS Interpreter Development)
find_package(OpenCV REQUIRED)
find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
    ${GTKMM_INCLUDE_DIRS}
)

add_executable(init src/initializer.cpp src/pqueue.cpp src/semaphoreop.cpp)
target_include_directories(init PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(init ${OpenCV_LIBS} Python3::Python)

add_executable(capture src/capture.cpp src/pqueue.cpp src/semaphoreop.cpp)
target_link_libraries(capture ${OpenCV_LIBS})

add_executable(convert src/convert.cpp src/pqueue.cpp src/semaphoreop.cpp) 
target_link_libraries(convert ${OpenCV_LIBS})

add_executable(draw src/draw.cpp src/pqueue.cpp src/semaphoreop.cpp) 
target_link_libraries(draw ${OpenCV_LIBS})

add_executable(destroyer src/destroyer.cpp src/pqueue.cpp src/semaphoreop.cpp) 
target_link_libraries(destroyer ${OpenCV_LIBS})

add_executable(configure src/configure.cpp)
target_link_libraries(configure ${OpenCV_LIBS})
