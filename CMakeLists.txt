cmake_minimum_required(VERSION 3.17)
project(qproperty_performance_report)

set (CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(OpenMP)

add_executable(main main.cpp PubSub.h qproperty_memory_measurement.cpp qproperty_memory_measurement.h property_memory_measurement.cpp property_memory_measurement.h configuration.h PubSub.cpp)
target_link_libraries(main Qt6::Core Qt::CorePrivate OpenMP::OpenMP_CXX)
