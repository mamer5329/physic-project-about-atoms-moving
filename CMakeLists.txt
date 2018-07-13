cmake_minimum_required(VERSION 3.9)
project(projekt_na_fizyke)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp doswiadczenie.cpp doswiadczenie.h atomy.cpp atomy.h)
add_executable(projekt_na_fizyke ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(projekt_na_fizyke ${SFML_LIBRARIES})
endif()
