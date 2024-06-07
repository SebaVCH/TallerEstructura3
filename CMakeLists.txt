cmake_minimum_required(VERSION 3.28)
project(TallerEstructura3)

set(CMAKE_CXX_STANDARD 26)

add_executable(TallerEstructura3 src/src/main.cpp
        src/src/transaccion.cpp
        src/include/transaccion.h
        src/src/persona.cpp
        src/include/persona.h
        src/src/arbolAVL.cpp
        src/include/arbolAVL.h
        src/src/Nodo.cpp
        src/include/Nodo.h)
