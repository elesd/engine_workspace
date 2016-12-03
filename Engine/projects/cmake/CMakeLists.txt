cmake_minimum_required (VERSION 2.8.11)
project (Engine)

set (${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0)
set (${CMAKE_PROJECT_NAME}_VERSION_MINOR 1)
set (${CMAKE_PROJECT_NAME}_VERSION_COUNTER 1)
string(TIMESTAMP ${CMAKE_PROJECT_NAME}_VERSION_YEAR "%y" UTC)
string(TIMESTAMP ${CMAKE_PROJECT_NAME}_VERSION_MONTH "%m" UTC)
string(TIMESTAMP ${CMAKE_PROJECT_NAME}_VERSION_DAY "%d" UTC)

set (MAIN_PROJECT_DIR "${PROJECT_SOURCE_DIR}/../..")
set (SOURCE_DIR "${MAIN_PROJECT_DIR}/source")
set (EXTERNALS_DIR "${MAIN_PROJECT_DIR}/../CommonLibs")
set (INSTALL_DIR "${EXTERNALS_DIR}/engine")

include(../../../CommonConfig.txt)

if (USE_GCC)
  include (GccConfig.txt)
elseif (USE_CL)
  include (ClConfig.txt)
endif (USE_GCC)

if (USE_64_BIT)
  set (EXECUTABLE_OUTPUT_PATH ${MAIN_PROJECT_DIR}/build/x64)
else (USE_64_BIT)
  set (EXECUTABLE_OUTPUT_PATH ${MAIN_PROJECT_DIR}/build/x32)
endif (USE_64_BIT)

configure_file (
		"${MAIN_PROJECT_DIR}/source/engine/engine_config.h.in"
		"${MAIN_PROJECT_DIR}/source/engine/EngineConfig.h")

file (GLOB src_ "${SOURCE_DIR}/engine/*.cpp")
file (GLOB src_app "${SOURCE_DIR}/engine/app/*.cpp")
file (GLOB src_app_winapi "${SOURCE_DIR}/engine/app/winapi/*.cpp")
file (GLOB src_app_winapi_empty "${SOURCE_DIR}/engine/app/winapi/empty/*.cpp")
file (GLOB src_constraints "${SOURCE_DIR}/engine/constraints/*.cpp")
file (GLOB src_environmentBuilder "${SOURCE_DIR}/engine/environmentBuilder/*.cpp")
file (GLOB src_exceptions "${SOURCE_DIR}/engine/exceptions/*.cpp")
file (GLOB src_functional "${SOURCE_DIR}/engine/functional/*.cpp")
file (GLOB src_inputs "${SOURCE_DIR}/engine/inputs/*.cpp")
file (GLOB src_moduls_sdl "${SOURCE_DIR}/engine/modules/sdl/*.cpp")
file (GLOB src_moduls_sdl_empty "${SOURCE_DIR}/engine/modules/sdl/empty/*.cpp")
file (GLOB src_moduls_glfw "${SOURCE_DIR}/engine/modules/glfw/*.cpp")
file (GLOB src_moduls_glfw_empty "${SOURCE_DIR}/engine/modules/glfw/empty/*.cpp")
file (GLOB src_moduls_winapi "${SOURCE_DIR}/engine/modules/winapi/*.cpp")
file (GLOB src_moduls_winapi_empty "${SOURCE_DIR}/engine/modules/winapi/empty/*.cpp")
file (GLOB src_signalSlot "${SOURCE_DIR}/engine/signalSlot/*.cpp")
file (GLOB src_stateStack "${SOURCE_DIR}/engine/stateStack/*.cpp")
file (GLOB src_test "${SOURCE_DIR}/engine/test/*.cpp")
file (GLOB src_video "${SOURCE_DIR}/engine/video/*.cpp")
file (GLOB src_video_winapi "${SOURCE_DIR}/engine/video/winapi/*.cpp")
file (GLOB src_video_winapi_empty "${SOURCE_DIR}/engine/video/winapi/empty/*.cpp")
file (GLOB src_video_glfw "${SOURCE_DIR}/engine/video/glfw/*.cpp")
file (GLOB src_video_glfw_empty "${SOURCE_DIR}/engine/video/glfw/empty/*.cpp")
file (GLOB src_utils "${SOURCE_DIR}/engine/utils/*.cpp")
file (GLOB src_view "${SOURCE_DIR}/engine/view/*.cpp")
file (GLOB src_view_glfw "${SOURCE_DIR}/engine/view/glfw/*.cpp")
file (GLOB src_view_glfw_empty "${SOURCE_DIR}/engine/view/glfw/empty/*.cpp")
file (GLOB src_view_sdl "${SOURCE_DIR}/engine/view/sdl/*.cpp")
file (GLOB src_view_sdl_empty "${SOURCE_DIR}/engine/view/sdl/empty/*.cpp")
file (GLOB src_view_winapi "${SOURCE_DIR}/engine/view/winapi/*.cpp")
file (GLOB src_view_winapi_empty "${SOURCE_DIR}/engine/view/winapi/empty/*.cpp")
file (GLOB src_pch "${MAIN_PROJECT_DIR}/pch/*.cpp")

file (GLOB header_ "${SOURCE_DIR}/engine/*.h")
file (GLOB header_app "${SOURCE_DIR}/engine/app/*.h*")
file (GLOB header_app_winapi "${SOURCE_DIR}/engine/app/winapi/*.h*")
file (GLOB header_constraints "${SOURCE_DIR}/engine/constraints/*.h*")
file (GLOB header_environmentBuilder "${SOURCE_DIR}/engine/environmentBuilder/*.h*")
file (GLOB header_exceptions "${SOURCE_DIR}/engine/exceptions/*.h")
file (GLOB header_functional "${SOURCE_DIR}/engine/functional/*.h*")
file (GLOB header_inputs "${SOURCE_DIR}/engine/inputs/*.h*")
file (GLOB header_moduls_sdl "${SOURCE_DIR}/engine/modules/sdl/*.h*")
file (GLOB header_moduls_glfw "${SOURCE_DIR}/engine/modules/glfw/*.h*")
file (GLOB header_moduls_winapi "${SOURCE_DIR}/engine/modules/winapi/*.h*")
file (GLOB header_signalSlot "${SOURCE_DIR}/engine/signalSlot/*.h*")
file (GLOB header_stateStack "${SOURCE_DIR}/engine/stateStack/*.h*")
file (GLOB header_test "${SOURCE_DIR}/engine/test/*.h*")
file (GLOB header_video "${SOURCE_DIR}/engine/video/*.h*")
file (GLOB header_video_winapi "${SOURCE_DIR}/engine/video/winapi/*.h*")
file (GLOB header_video_glfw "${SOURCE_DIR}/engine/video/glfw/*.h")
file (GLOB header_utils "${SOURCE_DIR}/engine/utils/*.h*")
file (GLOB header_view "${SOURCE_DIR}/engine/view/*.h*")
file (GLOB header_view_glfw "${SOURCE_DIR}/engine/view/glfw/*.h*")
file (GLOB header_view_sdl "${SOURCE_DIR}/engine/view/sdl/*.h*")
file (GLOB header_view_winapi "${SOURCE_DIR}/engine/view/winapi/*.h*")
file (GLOB header_pch "${MAIN_PROJECT_DIR}/pch/*.h*")

SOURCE_GROUP (engine FILES ${src_} ${header_})
SOURCE_GROUP (engine\\app FILES ${src_app} ${header_app})
SOURCE_GROUP (engine\\app\\winapi FILES ${src_app_winapi} ${header_app_winapi})
SOURCE_GROUP (engine\\app\\winapi\\empty FILES ${src_app_winapi_empty})
SOURCE_GROUP (engine\\constraints FILES ${src_constraints} ${header_constraints})
SOURCE_GROUP (engine\\environmentBuilder FILES ${src_environmentBuilder} ${header_environmentBuilder})
SOURCE_GROUP (engine\\exceptions FILES ${src_exceptions} ${header_exceptions})
SOURCE_GROUP (engine\\functional FILES ${src_functional} ${header_functional})
SOURCE_GROUP (engine\\inputs FILES ${src_inputs} ${header_inputs})
SOURCE_GROUP (engine\\modules\\sdl FILES ${src_moduls_sdl} ${header_moduls_sdl})
SOURCE_GROUP (engine\\modules\\sdl\\empty FILES ${src_moduls_sdl_empty})
SOURCE_GROUP (engine\\modules\\glwf FILES ${src_moduls_glfw} ${header_moduls_glfw})
SOURCE_GROUP (engine\\modules\\glwf\\empty FILES ${src_moduls_glfw_empty})
SOURCE_GROUP (engine\\modules\\winapi FILES ${src_moduls_winapi} ${header_moduls_winapi})
SOURCE_GROUP (engine\\modules\\winapi\\empty FILES ${src_moduls_winapi_empty})
SOURCE_GROUP (engine\\signalSlot FILES ${src_signalSlot} ${header_signalSlot})
SOURCE_GROUP (engine\\stateStack FILES ${src_stateStack} ${header_stateStack})
SOURCE_GROUP (engine\\test FILES ${src_test} ${header_test})
SOURCE_GROUP (engine\\video FILES ${src_video} ${header_video})
SOURCE_GROUP (engine\\video\\winapi FILES ${src_video_winapi} ${header_video_winapi})
SOURCE_GROUP (engine\\video\\winapi\\empty FILES ${src_video_winapi_empty})
SOURCE_GROUP (engine\\video\\glfw FILES ${src_video_glfw} ${header_video_glfw})
SOURCE_GROUP (engine\\video\\glfw\\empty FILES ${src_video_glfw_empty})
SOURCE_GROUP (engine\\utils FILES ${src_utils} ${header_utils})
SOURCE_GROUP (engine\\view FILES ${src_view} ${header_view})
SOURCE_GROUP (engine\\view\\glfw FILES ${src_view_glfw} ${header_view_glfw})
SOURCE_GROUP (engine\\view\\glfw\\empty FILES ${src_view_glfw_empty})
SOURCE_GROUP (engine\\view\\sdl FILES ${src_view_sdl} ${header_view_sdl})
SOURCE_GROUP (engine\\view\\sdl\\empty FILES ${src_view_sdl_empty})
SOURCE_GROUP (engine\\view\\winapi FILES ${src_view_winapi} ${header_view_winapi})
SOURCE_GROUP (engine\\view\\winapi\\empty FILES ${src_view_winapi_empty})
SOURCE_GROUP (engine\\pch FILES ${src_pch} ${header_pch})

include_directories("${MAIN_PROJECT_DIR}/pch")

if (DEBUG_BUILD)
  set (lib_name "Engine_d")
else (DEBUG_BUILD)
  set (lib_name "Engine")
endif (DEBUG_BUILD)

add_library (${lib_name} STATIC ${src_}
                           ${src_app} 
						   ${src_app_winapi} 
						   ${src_app_winapi_empty} 
                           ${src_constraints}
                           ${src_environmentBuilder}
                           ${src_exceptions}
                           ${src_functional}
                           ${src_inputs}
                           ${src_moduls_sdl}
                           ${src_moduls_sdl_empty}
                           ${src_moduls_glfw}
                           ${src_moduls_glfw_empty}
                           ${src_moduls_winapi}
                           ${src_moduls_winapi_empty}
                           ${src_signalSlot}
                           ${src_stateStack}
                           ${src_test}
                           ${src_utils}
                           ${src_view}
						   ${src_view_glfw}
						   ${src_view_glfw_empty}
						   ${src_view_sdl}
						   ${src_view_sdl_empty}
						   ${src_view_winapi}
						   ${src_view_winapi_empty}
						   ${src_video}
						   ${src_video_winapi}
						   ${src_video_winapi_empty}
						   ${src_video_glfw}
						   ${src_video_glfw_empty}
                           ${src_pch}
                           ${header_} 
                           ${header_app} 
						   ${header_app_winapi} 
                           ${header_constraints}
                           ${header_environmentBuilder}
                           ${header_exceptions}
                           ${header_functional}
                           ${header_inputs}
                           ${header_moduls_glfw}
                           ${header_moduls_sdl}
                           ${header_moduls_winapi}
                           ${header_signalSlot}
                           ${header_stateStack}
                           ${header_test}
                           ${header_utils}
                           ${header_view}
						   ${header_view_glfw}
						   ${header_view_sdl}
						   ${header_view_winapi}
						   ${header_video}
						   ${header_video_winapi}
						   ${header_video_glfw}
                           ${header_pch})

install (FILES ${header_} DESTINATION "${INSTALL_DIR}/include/engine")
install (FILES ${header_app} DESTINATION "${INSTALL_DIR}/include/engine/app")
install (FILES ${header_app_winapi} DESTINATION "${INSTALL_DIR}/include/engine/app/winapi")
install (FILES ${header_constraints} DESTINATION "${INSTALL_DIR}/include/engine/constraints")
install (FILES ${header_environmentBuilder} DESTINATION "${INSTALL_DIR}/include/engine/environmentBuilder")
install (FILES ${header_exceptions} DESTINATION "${INSTALL_DIR}/include/engine/exceptions")
install (FILES ${header_functional} DESTINATION "${INSTALL_DIR}/include/engine/functional")
install (FILES ${header_inputs} DESTINATION "${INSTALL_DIR}/include/engine/inputs")
install (FILES ${header_moduls_glfw} DESTINATION "${INSTALL_DIR}/include/engine/modules/glfw")
install (FILES ${header_moduls_sdl} DESTINATION "${INSTALL_DIR}/include/engine/modules/sdl")
install (FILES ${header_moduls_winapi} DESTINATION "${INSTALL_DIR}/include/engine/modules/winapi")
install (FILES ${header_signalSlot} DESTINATION "${INSTALL_DIR}/include/engine/signalSlot")
install (FILES ${header_stateStack} DESTINATION "${INSTALL_DIR}/include/engine/stateStack")
install (FILES ${header_test} DESTINATION "${INSTALL_DIR}/include/engine/test")
install (FILES ${header_utils} DESTINATION "${INSTALL_DIR}/include/engine/utils")
install (FILES ${header_view} DESTINATION "${INSTALL_DIR}/include/engine/view")
install (FILES ${header_view_winapi} DESTINATION "${INSTALL_DIR}/include/engine/view/winapi")
install (FILES ${header_view_glfw} DESTINATION "${INSTALL_DIR}/include/engine/view/glfw")
install (FILES ${header_view_sdl} DESTINATION "${INSTALL_DIR}/include/engine/view/sdl")
install (FILES ${header_video} DESTINATION "${INSTALL_DIR}/include/engine/video")
install (FILES ${header_video_winapi} DESTINATION "${INSTALL_DIR}/include/engine/video/winapi")
install (FILES ${header_video_glfw} DESTINATION "${INSTALL_DIR}/include/engine/video/glfw")


if (USE_64_BIT)
  install(TARGETS ${lib_name} DESTINATION "${INSTALL_DIR}/lib/x64/")
else (USE_64_BIT)
  install(TARGETS ${lib_name} DESTINATION "${INSTALL_DIR}/lib/x32/")
endif (USE_64_BIT)
