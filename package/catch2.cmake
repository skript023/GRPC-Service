include(FetchContent)

set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        devel
    GIT_PROGRESS TRUE
) 
message("catch2")

FetchContent_MakeAvailable(catch2)