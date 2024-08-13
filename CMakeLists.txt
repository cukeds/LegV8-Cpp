cmake_minimum_required(VERSION 3.28)
project(arm)

set(CMAKE_CXX_STANDARD 23)

add_executable(arm main.cpp
        Components/ProgramCounter.cpp
        Components/Processor.cpp
        Components/RegisterBank.cpp
        Components/Controls/Signal.cpp
        Components/SignExtend.h
        Components/SignExtend.cpp
        Display/Display.cpp
        Compiler/parser.h
)

include_directories(c:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML REQUIRED system window graphics)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(arm ${SFML_LIBRARIES})
endif()

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()