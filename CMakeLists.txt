cmake_minimum_required(VERSION 3.19)

project(Microservice CXX)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

include(CheckIncludeFileCXX)

if (MSVC)
    if("${CMAKE_MAKE_PROGRAM}" MATCHES "ninja")
        message("Ninja build system is being used.")
    else()
        include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        message("Ninja build system is not being used.")
    endif()
else()
    
endif()

#include external dependencies
#include(package/git.cmake)

message("\nFetching modules")
include(package/g3log.cmake)
include(package/fmtlib.cmake)
include(package/grpc.cmake)

file(GLOB_RECURSE DATAMODEL_PROTOS "${SRC_DIR}/**.proto")

if (MSVC)
    set(PROTOC "$ENV{VCPKG_ROOT}/installed/x64-windows/tools/protobuf/protoc.exe")
    set(GRPC_CPP_PLUGIN "$ENV{VCPKG_ROOT}/installed/x64-windows/tools/grpc/grpc_cpp_plugin.exe")
else()
    set(PROTOC "/mnt/j/database/Tools/vcpkg/installed/x64-linux/tools/protobuf/protoc")
    set(GRPC_CPP_PLUGIN "/mnt/j/database/Tools/vcpkg/installed/x64-linux/tools/grpc/grpc_cpp_plugin")
endif()

file(MAKE_DIRECTORY "${SRC_DIR}/protobuf")

message(STATUS "Compiling proto")
foreach(protos ${DATAMODEL_PROTOS})
    message(STATUS "Execute ${PROTOC} --grpc_out="${SRC_DIR}/protobuf" --cpp_out="${SRC_DIR}/protobuf" -I "${SRC_DIR}/proto" --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN}" "${proto_path}"")
    execute_process(
      COMMAND ${PROTOC} --grpc_out=${SRC_DIR}/protobuf --cpp_out=${SRC_DIR}/protobuf -I ${SRC_DIR}/proto --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN} ${protos}
        RESULT_VARIABLE GRPC_RESULT)
    if (GRPC_RESULT)
        message(FATAL_ERROR "grpc generate failed with error code: ${GRPC_RESULT}")
    else()
        message(STATUS "${protos} compiled")
    endif()
endforeach(protos)

# Microservice
message(STATUS "Microservice")
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.hxx"
    "${SRC_DIR}/**.hh"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  enable_language("RC")
  set (ICON ${SRC_DIR}/gaboot_icon.rc)
endif()

# Define a custom target to associate with the custom command
add_custom_target(proto DEPENDS "${SRC_DIR}/protobuf")

add_executable(Microservice "${SRC_DIR}/main.cpp")
add_dependencies(Microservice proto)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Microservice PROPERTY CXX_STANDARD 20) # 23 Because std::format is not avalible in std:c++20 for some reason. Maybe it's because i use v142 toolset.
# set_property(TARGET Microservice PROPERTY ISPC_INSTRUCTION_SETS avx2-i32x4)

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN})

target_include_directories(Microservice PRIVATE 
  ${SRC_DIR}
)

target_precompile_headers(Microservice PRIVATE "${SRC_DIR}/common.hpp")

target_link_libraries(Microservice PRIVATE 
fmt::fmt
gRPC::gpr 
gRPC::grpc 
gRPC::grpc++ 
gRPC::grpc++_alts 
gRPC::grpc++_reflection 
gRPC::grpc_plugin_support 
g3log 
absl::flags
absl::flags_parse
protobuf::libprotobuf)

# Warnings as errors
set_property(TARGET Microservice PROPERTY COMPILE_WARNING_AS_ERROR ON)
target_sources(Microservice PRIVATE ${SRC_MAIN})

add_compile_definitions(Microservice 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
)

# Add unit test build
#add_subdirectory(test)