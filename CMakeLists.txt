cmake_minimum_required(VERSION 3.1.0)
project(stx)

find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

set(SOURCES
    src/conversion.cpp
    src/curl.cpp
    src/filestream.cpp
    src/logger.cpp
    src/memorystream.cpp
    src/path.cpp
    src/request.cpp
    src/socket.cpp
    src/socketserver.cpp
    src/stream.cpp
    src/string.cpp
    src/textserializer.cpp
    src/url.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE True)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED True)

target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC include/stx)
target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})
