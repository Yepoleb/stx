cmake_minimum_required(VERSION 3.1.0)
project(stx)

find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

set(SOURCES
    src/byteserializer.cpp
    src/conversion.cpp
    src/curl.cpp
    src/filestream.cpp
    src/ipaddress.cpp
    src/logger.cpp
    src/memorystream.cpp
    src/path.cpp
    src/request.cpp
    src/socket.cpp
    src/socketserver.cpp
    src/stream.cpp
    src/string.cpp
    src/textserializer.cpp
    src/time.cpp
    src/url.cpp)

option(BUILD_SHARED_LIBS "Build library as a shared object")
add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE True)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED True)

target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS ${PROJECT_NAME} EXPORT stxTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(DIRECTORY include/stx DESTINATION include)

export(EXPORT stxTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/stx/stxTargets.cmake"
    NAMESPACE Upstream::
)
configure_file(cmake/stxConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/stx/stxConfig.cmake"
    COPYONLY
)

set(ConfigPackageLocation lib/cmake/stx)
install(EXPORT stxTargets
    FILE stxTargets.cmake
    NAMESPACE Upstream::
    DESTINATION ${ConfigPackageLocation}
)
install(FILES cmake/stxConfig.cmake DESTINATION ${ConfigPackageLocation})
