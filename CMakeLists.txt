cmake_minimum_required(VERSION 3.0)

project(SimpleCollision VERSION 1.0 LANGUAGES CXX) 

include_directories(include)
add_library(lib src/Canvas.cpp src/MainFrame.cpp src/Object.cpp)

find_package(wxWidgets REQUIRED core)
include(${wxWidgets_USE_FILE})

add_executable(SimpleCollision apps/App.cpp)
target_link_libraries(SimpleCollision lib ${wxWidgets_LIBRARIES})

add_compile_options(-g -pedantic -Wall -Wextra) 
