cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)


set(CMAKE_CXX_STANDARD 11)

add_compile_options("-lboost_system")
link_libraries("-lboost_system -lpthread")
include_directories (include)
include_directories (src)
add_executable(Boost_Echo_Client
        src/Client.cpp
        src/connectionHandler.cpp
        src/Book.cpp
        src/KeyboardReader.cpp
        src/readFromServ.cpp
        src/StompBookClubClient.cpp
        include/Book.h
        include/Client.h
        include/connectionHandler.h
        include/KeyboardReader.h
        include/readFromServ.h
        include/StompBookClubClient.h
        )