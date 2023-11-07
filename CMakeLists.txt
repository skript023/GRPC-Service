cmake_minimum_required(VERSION 3.19)

project(Microservice CXX)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

include(CheckIncludeFileCXX)

if (WIN32)
  message("Building on Windows")
  include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
elseif(UNIX)
  message("Building on a Unix-based platform (including Linux)")
  include("/mnt/j/database/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake")
else()
  message(FATAL "Building on an unknown or unsupported platform")
  # Add default configurations or actions here
endif()

#include external dependencies
include(package/git.cmake)

message("\nFetching modules")
include(package/g3log.cmake)
include(package/fmtlib.cmake)
include(package/grpc.cmake)
include(package/sqlite.cmake)
include(package/catch2.cmake)

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

add_executable(Microservice "${SRC_DIR}/main.cpp" ${ICON})

file(GLOB_RECURSE DATAMODEL_PROTOS "${SRC_DIR}/**.proto")

if (MSVC)
    set(PROTOC "$ENV{VCPKG_ROOT}/installed/x64-windows/tools/protobuf/protoc.exe")
    set(GRPC_CPP_PLUGIN "$ENV{VCPKG_ROOT}/installed/x64-windows/tools/grpc/grpc_cpp_plugin.exe")
else()
    set(PROTOC "/mnt/j/database/Tools/vcpkg/installed/x64-linux/tools/protobuf/protoc")
    set(GRPC_CPP_PLUGIN "/mnt/j/database/Tools/vcpkg/installed/x64-linux/tools/grpc/grpc_cpp_plugin")
endif()

file(MAKE_DIRECTORY "${SRC_DIR}/protobuf")

foreach(protos ${DATAMODEL_PROTOS})
    get_filename_component(source_name ${protos} NAME_WE)

    add_custom_command(
      OUTPUT "${SRC_DIR}/protobuf/${source_name}.pb.cc" "${SRC_DIR}/protobuf/${source_name}.pb.h"
      COMMAND ${PROTOC}
      ARGS --grpc_out ${SRC_DIR}/protobuf
        --cpp_out ${SRC_DIR}/protobuf
        -I ${SRC_DIR}/proto
        --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN}"
        ${protos}
      DEPENDS ${protos})

    # Define a custom target to associate with the custom command
    add_custom_target(${source_name} DEPENDS "${SRC_DIR}/protobuf/${source_name}.pb.cc" "${SRC_DIR}/protobuf/${source_name}.pb.h")
    add_dependencies(Microservice ${source_name})
endforeach(protos)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Microservice PROPERTY CXX_STANDARD 20) # 23 Because std::format is not avalible in std:c++20 for some reason. Maybe it's because i use v142 toolset.
# set_property(TARGET Microservice PROPERTY ISPC_INSTRUCTION_SETS avx2-i32x4)

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN})

target_include_directories(Microservice PRIVATE 
  ${SRC_DIR}
  "${catch2_SOURCE_DIR}/src"
)

target_precompile_headers(Microservice PRIVATE "${SRC_DIR}/common.hpp")

target_link_libraries(Microservice PRIVATE 
sqlite_orm::sqlite_orm
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
add_subdirectory(test)