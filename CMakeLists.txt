cmake_minimum_required (VERSION 2.8.11)
project (SQLiteInjector)

include_directories(~/boost_1_60_0/)
add_definitions(-DSQLITE_HAS_CODEC)
add_executable (SQLiteInjector main.cpp sqlite/sqlite3.c)