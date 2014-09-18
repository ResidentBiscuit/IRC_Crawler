# Project CrawlIRC
#
# Written by Jared Ready
# 09/18/2014

cmake_minimum_required(VERSION 2.8)
project(CRAWLIRC)

#Get all source files
file(GLOB_RECURSE CRAWLIRC_SOURCES "src/*.cpp")
file(GLOB_RECURSE CRAWLIRC_HEADERS "src/*.hpp")

set(CRAWLIRC_INCLUDE_DIRS "")
foreach(_headerFile ${CRAWLIRC_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND CRAWLIRC_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES CRAWLIRC_INCLUDE_DIRS)
include_directories(${CHESSPP_INCLUDE_DIRS})

#C++11
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

#Add CMAKE modules path for detecting libraries
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#Add pthread
find_package(Threads)

#Detect and add Boost
find_package(Boost 1.55.0 COMPONENTS system REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${BOOST_ROOT}/lib)
else()
    message(FATAL_ERROR "Boost not found by find_package. Try specifying BOOST_ROOT")
endif()

add_executable(crawlirc ${CRAWLIRC_SOURCES})
target_link_libraries(crawlirc ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
