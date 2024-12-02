cmake_minimum_required(VERSION 3.29)
project(fileZipper_)

set(CMAKE_CXX_STANDARD 17)

add_executable(fileZipper_ main.cpp
        priority_queue.cpp
        priority_queue.h
        HuffmanTree.cpp
        HuffmanTree.h
        FileZipper.cpp
        FileZipper.h
        LinkedList.cpp
        LinkedList.h
        main.cpp
        HuffmanNode.h
)
set(SOURCE_FILES main.cpp
        Google_tests/test_filezipper.cpp)
add_executable(Code_lib_run ${SOURCE_FILES}
        Google_tests/test_filezipper.cpp)

