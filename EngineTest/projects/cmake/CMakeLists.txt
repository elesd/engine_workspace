cmake_minimum_required (VERSION 2.6)
project (EngineTest)

set (${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0)
set (${CMAKE_PROJECT_NAME}_VERSION_MINOR 1)
set (${CMAKE_PROJECT_NAME}_VERSION_COUNTER 1)
string(TIMESTAMP ${CMAKE_PROJECT_NAME}_VERSION_YEAR "%y" UTC)
string(TIMESTAMP ${CMAKE_PROJECT_NAME}_VERSION_MONTH "%m" UTC)
string(TIMESTAMP ${CMAKE_PROJECT_NAME}_VERSION_DAY "%d" UTC)

set (MAIN_PROJECT_DIR "${PROJECT_SOURCE_DIR}/../..")
set (SOURCE_DIR "${MAIN_PROJECT_DIR}/source")
set (ENGINE_DIR "${MAIN_PROJECT_DIR}/../Engine/source")
set (EXTERNALS_DIR "${MAIN_PROJECT_DIR}/../CommonLibs")
set (DIRECTX_DIR "e:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")

include(../../../CommonConfig.txt)

if (USE_64_BIT)
  set (EXECUTABLE_OUTPUT_PATH ${MAIN_PROJECT_DIR}/build/x64)
else (USE_64_BIT)
  set (EXECUTABLE_OUTPUT_PATH ${MAIN_PROJECT_DIR}/build/x32)
endif (USE_64_BIT)

configure_file (
		"${MAIN_PROJECT_DIR}/source/enginetest_config.h.in"
		"${MAIN_PROJECT_DIR}/source/EngineTestConfig.h")

file (GLOB src_ "${SOURCE_DIR}/*.cpp")
file (GLOB src_functional "${SOURCE_DIR}/functional/*.cpp")
file (GLOB src_signalSlot "${SOURCE_DIR}/signalSlot/*.cpp")
file (GLOB src_stateStack "${SOURCE_DIR}/stateStack/*.cpp")
file (GLOB src_pch "${MAIN_PROJECT_DIR}/pch/*.cpp")

file (GLOB header_ "${SOURCE_DIR}/*.h")
file (GLOB header_functional "${SOURCE_DIR}/functional/*.h*")
file (GLOB header_signalSlot "${SOURCE_DIR}/signalSlot/*.h*")
file (GLOB header_stateStack "${SOURCE_DIR}/stateStack/*.h*")
file (GLOB header_pch "${MAIN_PROJECT_DIR}/pch/*.h*")

file (GLOB engine_src_ "${ENGINE_DIR}/engine/*.cpp")
file (GLOB engine_src_app "${ENGINE_DIR}/engine/app/*.cpp")
file (GLOB engine_src_app_winapi "${ENGINE_DIR}/engine/app/winapi/*.cpp")
file (GLOB engine_src_app_winapi_empty "${ENGINE_DIR}/engine/app/winapi/empty/*.cpp")
file (GLOB engine_src_constraints "${ENGINE_DIR}/engine/constraints/*.cpp")
file (GLOB engine_src_environmentBuilder "${ENGINE_DIR}/engine/environmentBuilder/*.cpp")
file (GLOB engine_src_functional "${ENGINE_DIR}/engine/functional/*.cpp")
file (GLOB engine_src_inputs "${ENGINE_DIR}/engine/inputs/*.cpp")
file (GLOB engine_src_moduls_sdl "${ENGINE_DIR}/engine/modules/sdl/*.cpp")
file (GLOB engine_src_moduls_sdl_empty "${ENGINE_DIR}/engine/modules/sdl/empty/*.cpp")
file (GLOB engine_src_moduls_glfw "${ENGINE_DIR}/engine/modules/glfw/*.cpp")
file (GLOB engine_src_moduls_glfw_empty "${ENGINE_DIR}/engine/modules/glfw/empty/*.cpp")
file (GLOB engine_src_moduls_winapi "${ENGINE_DIR}/engine/modules/winapi/*.cpp")
file (GLOB engine_src_moduls_winapi_empty "${ENGINE_DIR}/engine/modules/winapi/empty/*.cpp")
file (GLOB engine_src_signalSlot "${ENGINE_DIR}/engine/signalSlot/*.cpp")
file (GLOB engine_src_stateStack "${ENGINE_DIR}/engine/stateStack/*.cpp")
file (GLOB engine_src_test "${ENGINE_DIR}/engine/test/*.cpp")
file (GLOB engine_src_video "${ENGINE_DIR}/engine/video/*.cpp")
file (GLOB engine_src_video_winapi "${ENGINE_DIR}/engine/video/winapi/*.cpp")
file (GLOB engine_src_video_winapi_empty "${ENGINE_DIR}/engine/video/winapi/empty*.cpp")
file (GLOB engine_src_utils "${ENGINE_DIR}/engine/utils/*.cpp")
file (GLOB engine_src_view "${ENGINE_DIR}/engine/view/*.cpp")
file (GLOB engine_src_view_glfw "${ENGINE_DIR}/engine/view/glfw/*.cpp")
file (GLOB engine_src_view_glfw_empty "${ENGINE_DIR}/engine/view/glfw/empty/*.cpp")
file (GLOB engine_src_view_sdl "${ENGINE_DIR}/engine/view/sdl/*.cpp")
file (GLOB engine_src_view_sdl_empty "${ENGINE_DIR}/engine/view/sdl/empty/*.cpp")
file (GLOB engine_src_view_winapi "${ENGINE_DIR}/engine/view/winapi/*.cpp")
file (GLOB engine_src_view_winapi_empty "${ENGINE_DIR}/engine/view/winapi/empty/*.cpp")

file (GLOB engine_header_ "${ENGINE_DIR}/engine/*.h")
file (GLOB engine_header_app "${ENGINE_DIR}/engine/app/*.h*")
file (GLOB engine_header_app_winapi "${ENGINE_DIR}/engine/app/winapi/*.h*")
file (GLOB engine_header_constraints "${ENGINE_DIR}/engine/constraints/*.h*")
file (GLOB engine_header_environmentBuilder "${ENGINE_DIR}/engine/environmentBuilder/*.h*")
file (GLOB engine_header_functional "${ENGINE_DIR}/engine/functional/*.h*")
file (GLOB engine_header_inputs "${ENGINE_DIR}/engine/inputs/*.h*")
file (GLOB engine_header_moduls_sdl "${ENGINE_DIR}/engine/modules/sdl/*.h*")
file (GLOB engine_header_moduls_glfw "${ENGINE_DIR}/engine/modules/glfw/*.h*")
file (GLOB engine_header_moduls_winapi "${ENGINE_DIR}/engine/modules/winapi/*.h*")
file (GLOB engine_header_signalSlot "${ENGINE_DIR}/engine/signalSlot/*.h*")
file (GLOB engine_header_stateStack "${ENGINE_DIR}/engine/stateStack/*.h*")
file (GLOB engine_header_test "${ENGINE_DIR}/engine/test/*.h*")
file (GLOB engine_header_video "${ENGINE_DIR}/engine/video/*.h*")
file (GLOB engine_header_video_winapi "${ENGINE_DIR}/engine/video/winapi/*.h*")
file (GLOB engine_header_utils "${ENGINE_DIR}/engine/utils/*.h*")
file (GLOB engine_header_view "${ENGINE_DIR}/engine/view/*.h*")
file (GLOB engine_header_view_glfw "${ENGINE_DIR}/engine/view/glfw/*.h*")
file (GLOB engine_header_view_sdl "${ENGINE_DIR}/engine/view/sdl/*.h*")
file (GLOB engine_header_view_winapi "${ENGINE_DIR}/engine/view/winapi/*.h*")

SOURCE_GROUP (engine FILES ${engine_src_} ${engine_header_})
SOURCE_GROUP (engine\\app FILES ${engine_src_app} ${engine_header_app})
SOURCE_GROUP (engine\\app\\winapi FILES ${engine_src_app_winapi} ${engine_header_app_winapi})
SOURCE_GROUP (engine\\app\\winapi\\empty FILES ${engine_src_app_winapi_empty})
SOURCE_GROUP (engine\\constraints FILES ${engine_src_constraints} ${engine_header_constraints})
SOURCE_GROUP (engine\\environmentBuilder FILES ${engine_src_environmentBuilder} ${engine_header_environmentBuilder})
SOURCE_GROUP (engine\\functional FILES ${engine_src_functional} ${engine_header_functional})
SOURCE_GROUP (engine\\inputs FILES ${engine_src_inputs} ${engine_header_inputs})
SOURCE_GROUP (engine\\modules\\sdl FILES ${engine_src_moduls_sdl} ${engine_header_moduls_sdl})
SOURCE_GROUP (engine\\modules\\sdl\\empty FILES ${engine_src_moduls_sdl_empty})
SOURCE_GROUP (engine\\modules\\glwf FILES ${engine_src_moduls_glfw} ${engine_header_moduls_glfw})
SOURCE_GROUP (engine\\modules\\glwf\\empty FILES ${engine_src_moduls_glfw_empty})
SOURCE_GROUP (engine\\modules\\winapi FILES ${engine_src_moduls_winapi} ${engine_header_moduls_winapi})
SOURCE_GROUP (engine\\modules\\winapi\\empty FILES ${engine_src_moduls_winapi_empty})
SOURCE_GROUP (engine\\signalSlot FILES ${engine_src_signalSlot} ${engine_header_signalSlot})
SOURCE_GROUP (engine\\stateStack FILES ${engine_src_stateStack} ${engine_header_stateStack})
SOURCE_GROUP (engine\\test FILES ${engine_src_test} ${engine_header_test})
SOURCE_GROUP (engine\\video FILES ${engine_src_video} ${engine_header_video})
SOURCE_GROUP (engine\\video\\winapi FILES ${engine_src_video_winapi} ${engine_header_video_winapi})
SOURCE_GROUP (engine\\video\\winapi\\empty FILES ${engine_src_video_winapi_empty})
SOURCE_GROUP (engine\\utils FILES ${engine_src_utils} ${engine_header_utils})
SOURCE_GROUP (engine\\view FILES ${engine_src_view} ${engine_header_view})
SOURCE_GROUP (engine\\view\\glfw FILES ${engine_src_view_glfw} ${engine_header_view_glfw})
SOURCE_GROUP (engine\\view\\glfw\\empty FILES ${engine_src_view_glfw_empty})
SOURCE_GROUP (engine\\view\\sdl FILES ${engine_src_view_sdl} ${engine_header_view_sdl})
SOURCE_GROUP (engine\\view\\sdl\\empty FILES ${engine_src_view_sdl_empty})
SOURCE_GROUP (engine\\view\\winapi FILES ${engine_src_view_winapi} ${engine_header_view_winapi})
SOURCE_GROUP (engine\\view\\winapi\\empty FILES ${engine_src_view_winapi_empty})


SOURCE_GROUP (src\\functional FILES ${src_functional} ${header_functional})
SOURCE_GROUP (src\\signalSlot FILES ${src_signalSlot} ${header_signalSlot})
SOURCE_GROUP (src\\stateStack FILES ${src_stateStack} ${header_stateStack})
SOURCE_GROUP (src\\pch FILES ${src_pch} ${header_pch})
SOURCE_GROUP (src FILES ${src_} ${header_})

include_directories("${MAIN_PROJECT_DIR}/pch")
include_directories("${ENGINE_DIR}")

add_executable(engineTest ${src_} 
                          ${src_functional}
                          ${src_stateStack}
                          ${src_signalSlot}
                          ${src_pch}
                          ${header_}
                          ${header_functional}
                          ${header_stateStack}
                          ${header_signalSlot}
                          ${header_pch}

                          ${engine_src_} 
                          ${engine_src_app} 
						  ${engine_src_app_winapi} 
						  ${engine_src_app_winapi_empty} 
                          ${engine_src_constraints}
                          ${engine_src_environmentBuilder}
                          ${engine_src_functional}
                          ${engine_src_inputs}
                          ${engine_src_moduls_sdl}
                          ${engine_src_moduls_sdl_empty}
                          ${engine_src_moduls_glfw}
                          ${engine_src_moduls_glfw_empty}
                          ${engine_src_moduls_winapi}
                          ${engine_src_moduls_winapi_empty}
                          ${engine_src_signalSlot}
                          ${engine_src_stateStack}
                          ${engine_src_test}
                          ${engine_src_utils}
                          ${engine_src_view}
						  ${engine_src_view_glfw}
						  ${engine_src_view_glfw_empty}
						  ${engine_src_view_sdl}
						  ${engine_src_view_sdl_empty}
						  ${engine_src_view_winapi}
						  ${engine_src_view_winapi_empty}
						  ${engine_src_video}
						  ${engine_src_video_winapi}
						  ${engine_src_video_winapi_empty}
                          ${engine_header_} 
                          ${engine_header_app} 
						  ${engine_header_app_winapi} 
                          ${engine_header_constraints}
                          ${engine_header_environmentBuilder}
                          ${engine_header_functional}
                          ${engine_header_inputs}
                          ${engine_header_moduls_glfw}
                          ${engine_header_moduls_sdl}
                          ${engine_header_moduls_winapi}
                          ${engine_header_signalSlot}
                          ${engine_header_stateStack}
                          ${engine_header_test}
                          ${engine_header_utils}
                          ${engine_header_view}
						  ${engine_header_view_glfw}
						  ${engine_header_view_sdl}
						  ${engine_header_view_winapi}
						  ${engine_header_video}
						  ${engine_header_video_winapi})

if (USE_GCC)
  include (GccConfig.txt)
elseif (USE_CL)
  include (ClConfig.txt)
endif (USE_GCC)
