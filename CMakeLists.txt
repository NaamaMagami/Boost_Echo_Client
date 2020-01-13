cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
link_libraries("-lboost_system")

add_executable(Boost_Echo_Client
    include/connectionHandler.h
    src/connectionHandler.cpp
    src/echoClient.cpp src/Client.cpp include/Client.h src/check.cpp include/check.h src/KeyboardReader.cpp include/KeyboardReader.h src/Book.cpp include/Book.h src/readFromServ.cpp include/readFromServ.h)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost 1.65.1 REQUIRED COMPONENTS
        date_time filesystem iostreams system)
find_package(Threads)
target_link_libraries(Boost_Echo_Client Boost::date_time Boost::filesystem
        Boost::iostreams Boost::system)