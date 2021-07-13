cmake_minimum_required(VERSION 3.0.0)
project(sorting-visualiser VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(sorting-visualiser ./src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


# the below line adds the linking functionality with the SFML library files, not too sure 
# how this works but it does
target_link_libraries(sorting-visualiser -lsfml-graphics -lsfml-window -lsfml-system) 