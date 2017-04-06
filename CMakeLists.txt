### CMakeLists.txt --- PolytechRayTracing project
## 
## Author: Jean-Christophe Lombardo
## Copyright (C) 2011 - Jean-Christophe Lombardo, Inria
## Created: Thu Jun  9 10:33:56 2011
## Last-Updated:  Thu Jun  9 17:26:50 2011
##           By: Jean-Christophe Lombardo
##
######################################################################
cmake_minimum_required(VERSION 2.8)

project(PolytechRayTracing)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

## #################################################################
## Setup CMake Modules
## #################################################################
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


## #################################################################
## Setup output paths
## #################################################################

set(CMAKE_DEBUG_POSTFIX "d")
### from osg CMakeLists.txt
IF(UNIX AND NOT WIN32 AND NOT APPLE)
  IF(CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET(LIB_POSTFIX "64" CACHE STRING "suffix for 32/64 dir placement")
      MARK_AS_ADVANCED(LIB_POSTFIX)
  ENDIF(CMAKE_SIZEOF_VOID_P MATCHES "8")
ENDIF(UNIX AND NOT WIN32 AND NOT APPLE)
IF(NOT DEFINED LIB_POSTFIX)
    SET(LIB_POSTFIX "")
ENDIF(NOT DEFINED LIB_POSTFIX)


if(WIN32)
  set(RUNTIME_OUTPUT_DIRECTORY bin)
  set(LIBRARY_OUTPUT_DIRECTORY bin)
  set(ARCHIVE_OUTPUT_DIRECTORY lib)
else(WIN32)
  set(RUNTIME_OUTPUT_DIRECTORY bin)
  set(LIBRARY_OUTPUT_DIRECTORY lib${LIB_POSTFIX})
  set(ARCHIVE_OUTPUT_DIRECTORY lib${LIB_POSTFIX})
endif(WIN32)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/${ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/${RUNTIME_OUTPUT_DIRECTORY})


## #################################################################
## Resolve dependencies
## #################################################################

## Library ITPP

#find_package(ITPP REQUIRED)
#if(ITPP_FOUND)
#    include_directories(${ITPP_INCLUDE_DIR})
#endif(ITPP_FOUND)

find_package(SDL REQUIRED)
if(SDL_FOUND)
    include_directories(${SDL_INCLUDE_DIR}/..)
endif(SDL_FOUND)

find_package(SDL_image REQUIRED)
if(SDLIMAGE_FOUND)
    include_directories(${SDLIMAGE_INCLUDE_DIR}/..)
endif(SDLIMAGE_FOUND)

## #################################################################
## Build our project
## #################################################################

#add_definitions(-std=c++0x)

add_subdirectory(src)

## -*- tab-width: 4; indent-tabs-mode: nil c-basic-offset: 4 -*-
## vim:cindent:ts=4:sw=4:et:tw=80:sta:

