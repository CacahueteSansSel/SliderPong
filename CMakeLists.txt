cmake_minimum_required(VERSION 3.7)
project(sliderpong)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        source/main.cpp
)

# Specify external includes here
include_directories("D:/devkitPro/libctru/include")
include_directories("D:/devkitPro/libcwav/include")
include_directories("D:/devkitPro/libncsnd/include")
include_directories("lib")

add_executable(sliderpong ${SOURCE_FILES})
