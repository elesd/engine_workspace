cmake_minimum_required (VERSION 2.6)
project (Tutorial)

set (${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0)
set (${CMAKE_PROJECT_NAME}_VERSION_MINOR 1)
set (${CMAKE_PROJECT_NAME}_VERSION_COUNTER 1)
string(TIMESTAMP ${CMAKE_PROJECT_NAME}_VERSION_YEAR "%y" UTC)
string(TIMESTAMP ${CMAKE_PROJECT_NAME}_VERSION_MONTH "%m" UTC)
string(TIMESTAMP ${CMAKE_PROJECT_NAME}_VERSION_DAY "%d" UTC)

set (MAIN_PROJECT_DIR "${PROJECT_SOURCE_DIR}/../..")
set (SOURCE_DIR "${MAIN_PROJECT_DIR}/source")
set (EXTERNALS_DIR "${MAIN_PROJECT_DIR}/../CommonLibs")
if (WIN32)
  set (VISUAL_STUDIO_DIR "c:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/lib/")
endif (WIN32)
include(../../../CommonConfig.txt)


set (EXECUTABLE_OUTPUT_PATH ${MAIN_PROJECT_DIR}/build/)

configure_file (
		"${MAIN_PROJECT_DIR}/source/Tutorial_config.h.in"
		"${MAIN_PROJECT_DIR}/source/TutorialConfig.h")

file (GLOB src_ "${SOURCE_DIR}/*.cpp")
file (GLOB src_states "${SOURCE_DIR}/states/*.cpp")
file (GLOB src_pch "${MAIN_PROJECT_DIR}/pch/*.cpp")

file (GLOB header_ "${SOURCE_DIR}/*.h*")
file (GLOB header_states "${SOURCE_DIR}/states/*.h*")
file (GLOB header_pch "${MAIN_PROJECT_DIR}/pch/*.h*")

SOURCE_GROUP (src\\pch FILES ${src_pch} ${header_pch})
SOURCE_GROUP (src\\states FILES ${src_states} ${header_states})
SOURCE_GROUP (src FILES ${src_} ${header_})

include_directories("${MAIN_PROJECT_DIR}/pch")

file (GLOB all_files ${src_} 
                       ${src_pch}
					   ${src_states}
                       ${header_}
                       ${header_pch}
					   ${header_states})

if (USE_WINAPI)
  add_executable(Tutorial WIN32 ${all_files})
else (USE_WINAPI)
  add_executable(Tutorial ${all_files})
endif (USE_WINAPI)

if (USE_GCC)
  include (GccConfig.txt)
elseif (USE_CL)
  include (ClConfig.txt)
endif (USE_GCC)
