cmake_minimum_required(VERSION 3.19)
project(Microservice_test CXX)

add_executable(Microservice_test test_main.cpp ${ICON})

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon
# target_link_libraries(${ PROJECT_NAME }_test PRIVATE drogon)
#
# and comment out the following lines
target_link_libraries(Microservice_test PRIVATE sqlite_orm::sqlite_orm Catch2::Catch2)

set_property(TARGET Microservice_test PROPERTY CXX_STANDARD 20)