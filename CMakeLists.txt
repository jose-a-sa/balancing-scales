cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BalancingScalesProblem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include(cmake/FetchFmtLib.cmake)
# include(cmake/FetchSpdLog.cmake)
# include(cmake/FetchCLI11.cmake)
# include(cmake/FetchGoogleTest.cmake)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(balance-scales src/main.cpp)
#target_link_libraries(balance-scales PRIVATE fmt::fmt)
