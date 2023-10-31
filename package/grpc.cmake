message("\nInstalling grpc library")
  
if (MSVC)
    # Set the path to vcpkg for Windows
    set(VCPKG_EXECUTABLE "J:/database/Tools/vcpkg/vcpkg.exe")
else()
    set(VCPKG_EXECUTABLE "/mnt/j/database/Tools/vcpkg/vcpkg")
    message("GCC is used")
endif()

find_package(gRPC)

if(NOT gRPC_FOUND)
    
    message(STATUS "gRPC not found. Attempting to install it.")
    execute_process(
    COMMAND "${VCPKG_EXECUTABLE}" install grpc
    RESULT_VARIABLE VCPKG_RESULT
    )

    if(VCPKG_RESULT)
        message(FATAL_ERROR "vcpkg failed with error code: ${VCPKG_RESULT}")
    else()
        message("gRPC has been successfully installed.")
    endif()

    find_package(gRPC CONFIG REQUIRED)

    if(gRPC_FOUND)
        message(STATUS "gRPC is already exist.")
        find_package(Protobuf CONFIG REQUIRED)
    else()
        message(FATAL_ERROR "gRPC not found even after attempting to install it.")
    endif()
else()
    message("gRPC is already exist, located in ${gRPC_INCLUDE_DIRS}")
    find_package(Protobuf CONFIG REQUIRED)
endif()