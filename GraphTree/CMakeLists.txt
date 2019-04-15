cmake_minimum_required(VERSION 3.12)
project(GraphTree)

set(CMAKE_CXX_STANDARD 17)


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build")

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate
include_directories(cmake-build-debug/googletest-src/googlemock/include)
include_directories(cmake-build-debug/googletest-src/googletest/include)


# add_subdirectory(lib/googletest-master)
# include_directories(lib/googletest-master/googletest/include)
# include_directories(lib/googletest-master/googlemock/include)

include_directories(DateTime/include)
include_directories(DateTime/src)

include_directories(Graph/include)
include_directories(Graph/src)

set(SOURCE_FILES src/main.cpp DateTime/src/DateTime.cpp DateTime/include/DateTime.h DateTime/include/DateTimeDelta.h DateTime/src/DateTimeDelta.cpp Graph/include/Graph.h dependencies/random.hpp Tests/tests.cpp)

add_executable(GraphTree ${SOURCE_FILES})

target_link_libraries(GraphTree  gtest gtest_main)

