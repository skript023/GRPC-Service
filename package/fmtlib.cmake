include(FetchContent)

set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
    fmtlib
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        master
    GIT_PROGRESS TRUE
) 
message("fmtlib")

FetchContent_MakeAvailable(fmtlib)