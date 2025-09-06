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


enable_testing()

file(GLOB TEST_INPUTS "${CMAKE_SOURCE_DIR}/tests/*.in")

foreach(input_file ${TEST_INPUTS})
    # Extract the test name (strip path + extension)
    get_filename_component(test_name ${input_file} NAME_WE)

    # Expected output file has same basename but .out extension
    set(output_file "${CMAKE_SOURCE_DIR}/tests/${test_name}.out")

    # Define the test only if output exists
    if(EXISTS ${output_file})
        add_test(NAME ${test_name}
            COMMAND bash -c "$<TARGET_FILE:balance-scales> < '${input_file}' | diff -w - '${output_file}'"
        )
    else()
        message(WARNING "Skipping test '${test_name}' because ${output_file} is missing")
    endif()
endforeach()

