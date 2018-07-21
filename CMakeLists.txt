cmake_minimum_required(VERSION 2.8)
PROJECT(genetic_tsp)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(genetic_tsp main.cpp simulation.cpp)
TARGET_LINK_LIBRARIES (genetic_tsp ${OpenCV_LIBS})
