cmake_minimum_required(VERSION 4.0)
project(sqlite_ejemplo)

message(STATUS "Compiling sqlite3...")
file( GLOB LIB_SOURCES lib/*.c )
file( GLOB LIB_HEADERS lib/*.h )
add_library( sqlite3 ${LIB_SOURCES} ${LIB_HEADERS} )
message(STATUS "Done compiling")


message(STATUS "Getting app sources")
file(GLOB APP_SOURCES src/*/*.cpp )
foreach(source ${APP_SOURCES})
    get_filename_component(nombre ${source} NAME_WE)
    message(STATUS "Source: " ${source} " Name: " ${nombre})
    add_executable(${nombre} ${source})
    target_link_libraries(${nombre} sqlite3)
endforeach(source ${APP_SOURCES})
