cmake_minimum_required(VERSION 3.19)
project(CSC2222_PapiDemo)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(PAPI REQUIRED)
message(STATUS ${PAPI_LIBRARIES})


set(CMAKE_CXX_STANDARD 14)

add_executable(CSC2222_PapiDemo main.cpp)
target_link_libraries(CSC2222_PapiDemo ${PAPI_LIBRARIES})