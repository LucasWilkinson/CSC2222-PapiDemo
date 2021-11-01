cmake_minimum_required(VERSION 3.19)
project(CSC2222_PapiDemo)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(PAPI REQUIRED)
message(STATUS ${PAPI_LIBRARIES})

set(CMAKE_CXX_STANDARD 14)

# Low Level Demo
add_executable(low_level_demo low_level_demo.cpp)
target_link_libraries(low_level_demo ${PAPI_LIBRARIES})

# High Level Demo
add_executable(high_level_demo high_level_demo.cpp)
target_link_libraries(high_level_demo ${PAPI_LIBRARIES})

# High Level Demo With Snapshotting
add_executable(high_level_demo_snapshotting high_level_demo.cpp)
target_link_libraries(high_level_demo_snapshotting ${PAPI_LIBRARIES})
target_compile_definitions(high_level_demo_snapshotting PUBLIC TILE_SNAPSHOTTING=1)