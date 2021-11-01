cmake_minimum_required(VERSION 3.00)
project(CSC2222_PapiDemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp ")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(PAPI REQUIRED)
message(STATUS "Found PAPI")
message(STATUS "   Papi lib: ${PAPI_LIBRARIES}")
message(STATUS "   Papi inc: ${PAPI_INCLUDE_DIRS}")

set(CMAKE_CXX_STANDARD 14)

macro(add_low_level_demo_executable)
    configure_file(low_level_demo.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/src/${ARGV0}.cpp @ONLY)
    add_executable(${ARGV0} ${CMAKE_CURRENT_BINARY_DIR}/src/${ARGV0}.cpp)
    target_link_libraries(${ARGV0} ${PAPI_LIBRARIES})
    target_include_directories(${ARGV0} PUBLIC ${PAPI_INCLUDE_DIRS})
    target_include_directories(${ARGV0} PUBLIC ${PROJECT_SOURCE_DIR})
endmacro()


# Low Level Demo - L1 Cache Misses
set(PAPI_EVENTS "PAPI_L1_DCM")
add_low_level_demo_executable(low_level_demo_l1)

# Low Level Demo - Flops
set(PAPI_EVENTS "PAPI_DP_OPS")
add_low_level_demo_executable(low_level_demo_flops)

# Low Level Demo - Flops + Vec Flops
set(PAPI_EVENTS "PAPI_DP_OPS, PAPI_VEC_DP")
add_low_level_demo_executable(low_level_demo_vec_flops)

# Low Level Demo - L1 Cache Misses + Flops
set(PAPI_EVENTS "PAPI_DP_OPS, PAPI_L1_DCM")
add_low_level_demo_executable(low_level_demo_l1_and_flops)

# Low Level Demo - L1 Cache Misses + Flops - Multiplexed
set(PAPI_EVENTS "PAPI_DP_OPS, PAPI_L1_DCM")
add_low_level_demo_executable(low_level_demo_l1_and_flops_multiplexed)
target_compile_definitions(low_level_demo_l1_and_flops_multiplexed PUBLIC MULTIPLEX=1)

# High Level Demo
add_executable(high_level_demo high_level_demo.cpp)
target_include_directories(high_level_demo PUBLIC ${PAPI_INCLUDE_DIRS})
target_link_libraries(high_level_demo ${PAPI_LIBRARIES})

# High Level Demo With Snapshotting
add_executable(high_level_demo_snapshotting high_level_demo.cpp)
target_link_libraries(high_level_demo_snapshotting ${PAPI_LIBRARIES})
target_include_directories(high_level_demo_snapshotting PUBLIC ${PAPI_INCLUDE_DIRS})
target_compile_definitions(high_level_demo_snapshotting PUBLIC TILE_SNAPSHOTTING=1)

# Memory Latency and Potential Gain Demo
add_executable(MemoryLatencyAndPotentialGain MemoryLatencyAndPotentialGain.cpp)
target_link_libraries(MemoryLatencyAndPotentialGain ${PAPI_LIBRARIES})
target_include_directories(MemoryLatencyAndPotentialGain PUBLIC ${PAPI_INCLUDE_DIRS})