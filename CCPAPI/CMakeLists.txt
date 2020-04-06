##########################################################################
#                                                                        #
#                               CCPAPI                                   #
#                                                                        #
#  This program is free software; you can redistribute it and/or modify  #
#  it under the terms of the GNU Library General Public License as       #
#  published by the Free Software Foundation; version 2 or later of the  #
#  License.                                                              #
#                                                                        #
#  This program is distributed in the hope that it will be useful,       #
#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
#  GNU General Public License for more details.                          #
#                                                                        #
#          Copyright 2020 Paul RASCLE www.openfields.fr                  #
#                                                                        #
##########################################################################

cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0071 NEW)
MESSAGE(STATUS "CC PYthon API")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

# --- C++ library cc Python Api (ccPApi)

include_directories( ${CC_FBO_LIB_SOURCE_DIR}/include )
include_directories( ${CC_CORE_LIB_SOURCE_DIR}/include )
include_directories( ${QCC_DB_LIB_SOURCE_DIR} )
if( MSVC )
   include_directories( ${QCC_DB_LIB_SOURCE_DIR}/msvc )
endif()
include_directories( ${QCC_IO_LIB_SOURCE_DIR} )
include_directories( ${QCC_GL_LIB_SOURCE_DIR} )
include_directories( ${CloudComparePlugins_SOURCE_DIR} )
include_directories( ${CloudCompare_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../common )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/db_tree )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/ui_templates )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../libs/qcustomplot )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

file( GLOB header_list *.h )
file( GLOB source_list *.cpp )

add_library( CC_PAPI_LIB STATIC ${header_list} ${source_list} )

target_link_libraries( CC_PAPI_LIB CC_FBO_LIB )
target_link_libraries( CC_PAPI_LIB CC_CORE_LIB )
target_link_libraries( CC_PAPI_LIB QCC_DB_LIB )
target_link_libraries( CC_PAPI_LIB QCC_IO_LIB )
target_link_libraries( CC_PAPI_LIB QCC_GL_LIB )
target_link_libraries( CC_PAPI_LIB qcustomplot )

#PROJECT( cloudCompare )
#SET(SIP_FILE cloudCompare.sip)

SET(Python_ADDITIONAL_VERSIONS 3.6) # priority to this version 
find_package(catkin REQUIRED)
catkin_package(CFG_EXTRAS python_qt_binding-extras.cmake)
catkin_python_setup()
INCLUDE(sip_helper)
build_sip_binding(cloudCompare cloudCompare.sip)
