cmake_minimum_required(VERSION 4.3)

project(eyeflow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)

add_executable(eyeflow main.cpp
        dotwidget/dotwidget.cpp
        dotwidget/dotwidget.h
        motion/motion.cpp
        motion/motion.h
)
target_link_libraries(eyeflow PRIVATE Qt6::Widgets)
target_compile_options(eyeflow PRIVATE -Wall -Wextra -Wconversion -Wshadow)
target_include_directories(eyeflow PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
