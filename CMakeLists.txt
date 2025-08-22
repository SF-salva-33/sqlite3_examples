project(sqlite)

add_executable(queries_complejos ./src/queries_complejos/queries_stmt.cpp ./lib/sqlite3.h ./lib/sqlite3.c)
add_executable(queries_sensillos ./src/queries_sensillos/queries_sensillo.cpp ./lib/sqlite3.h ./lib/sqlite3.c)
add_executable(intro ./src/introduccion/intro.cpp ./lib/sqlite3.h ./lib/sqlite3.c)