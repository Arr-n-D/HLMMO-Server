cmake_minimum_required(VERSION 3.18)

set(TARGET Server)

project(${TARGET} VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ENet REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${ENET_INCLUDE_DIRS} )
link_directories(${Boost_LIBRARY_DIRS})
add_subdirectory(sentry)

add_executable(${TARGET} 
    src/main.cpp
    src/NetworkManager.cpp
    src/Player.cpp
    src/Core.cpp
)

target_link_libraries(${TARGET} PRIVATE ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${ENET_LIBRARIES} sentry)

target_include_directories(${TARGET} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/enet
    ${PROJECT_SOURCE_DIR}/include/msgpack
)

