cmake_minimum_required(VERSION 3.0.0)
project(Telefonkonyv)

set(CMAKE_CXX_STANDARD 98)

file(GLOB TELEFONKONYV_SRC
     "src/*.h"
     "src/*.c"
)

add_executable(Telefonkonyv ${TELEFONKONYV_SRC})
