cmake_minimum_required(VERSION 3.10)
project(char_guessing_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Boost root directory
set(BOOST_ROOT "/Users/djmekki/.brew/opt/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")

# Find Boost libraries and headers
find_package(Boost REQUIRED COMPONENTS system filesystem)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(char_guessing_game main.cpp)
    target_link_libraries(char_guessing_game ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find Boost libraries")
endif()