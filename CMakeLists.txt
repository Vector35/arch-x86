cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(arch_x86)

if((NOT BN_API_PATH) AND (NOT BN_INTERNAL_BUILD))
	set(BN_API_PATH $ENV{BN_API_PATH})
	if(NOT BN_API_PATH)
		message(FATAL_ERROR "Provide path to Binary Ninja API source in BN_API_PATH")
	endif()
endif()
if(NOT BN_INTERNAL_BUILD)
	add_subdirectory(${BN_API_PATH} ${PROJECT_BINARY_DIR}/api)
endif()

file(GLOB SOURCES *.cpp *.h)

if(DEMO)
	add_library(arch_x86 STATIC ${SOURCES})
else()
	add_library(arch_x86 SHARED ${SOURCES})
endif()

target_include_directories(arch_x86
	PRIVATE ${PROJECT_SOURCE_DIR}
	PRIVATE ${PROJECT_SOURCE_DIR}/xedInc)

if(MSVC)
	set(XED_PLATFORM win)
	set(YASM_PATH win32/yasm.exe)
elseif(APPLE)
	set(XED_PLATFORM macos)
	set(YASM_PATH mac/yasm)
else()
	set(XED_PLATFORM linux)
	set(YASM_PATH linux/yasm)
endif()

find_library(XED_LIBRARY
	NAMES xed_${XED_PLATFORM}
	PATHS ${PROJECT_SOURCE_DIR}/lib
	REQUIRED NO_DEFAULT_PATH)
add_library(xed STATIC IMPORTED)
set_target_properties(xed PROPERTIES
	IMPORTED_LOCATION ${XED_LIBRARY})

target_link_libraries(arch_x86 binaryninjaapi xed)

if(UNIX AND NOT APPLE)
	target_link_options(arch_x86 PRIVATE "LINKER:--exclude-libs,ALL")
endif()

set_target_properties(arch_x86 PROPERTIES
    CXX_STANDARD 17
	CXX_VISIBILITY_PRESET hidden
	CXX_STANDARD_REQUIRED ON
    VISIBILITY_INLINES_HIDDEN ON
	POSITION_INDEPENDENT_CODE ON)

if(BN_INTERNAL_BUILD)
	plugin_rpath(arch_x86)
	set_target_properties(arch_x86 PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY ${BN_CORE_PLUGIN_DIR}
		RUNTIME_OUTPUT_DIRECTORY ${BN_CORE_PLUGIN_DIR})
	add_custom_command(TARGET arch_x86 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/yasm/${YASM_PATH} ${BN_CORE_PLUGIN_DIR})
endif()
