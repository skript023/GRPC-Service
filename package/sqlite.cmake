include(FetchContent)

set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
    sqlite
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
    GIT_TAG        master
    GIT_PROGRESS TRUE
) 
message("sqlite")

FetchContent_MakeAvailable(sqlite)