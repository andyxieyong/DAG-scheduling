cmake_minimum_required(VERSION 3.5)
project(dag-sched CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC -Wno-deprecated-declarations -Wno-unused-variable")

#-------------------------------------------------------------------------------
# External Libraries
#-------------------------------------------------------------------------------
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(yaml-cpp REQUIRED)

#-------------------------------------------------------------------------------
# Build libraries
#-------------------------------------------------------------------------------


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include matplotlib-cpp /usr/include/python3.8)

file(GLOB dag-sched-SRC "src/*/*.cpp" "src/*.cpp")
set(dag-sched-LIBS yaml-cpp python3.8)
add_library(dag-sched SHARED ${dag-sched-SRC})
target_link_libraries(dag-sched ${dag-sched-LIBS} )

#-------------------------------------------------------------------------------
# Build executables
#-------------------------------------------------------------------------------
add_executable(demo demo/main.cpp)
target_link_libraries(demo dag-sched)

add_executable(eval demo/evaluate.cpp)
target_link_libraries(eval dag-sched)
