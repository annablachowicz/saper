cmake_minimum_required(VERSION 2.8)

project(saper)
set(CMAKE_MODULE_PATH "../source/lib/SFML")
find_package(SFML 2.4 COMPONENTS graphics audio REQUIRED)
add_executable(${PROJECT_NAME} "main.cpp"
    "boardtile.h" "boardtile.cpp"
    "board.h" "board.cpp"
    "gamecontroller.h" "gamecontroller.cpp"
    "userdata.h" "userdata.cpp"
    "database.h" "database.cpp"
    "selector.h" "selector.cpp")
target_link_libraries(saper sfml-system sfml-window sfml-graphics sfml-network sfml-audio)


project(saper)
set(CMAKE_MODULE_PATH "../source/lib/sqlite_orm-master")
find_package (SQLite3)
if (SQLITE3_FOUND)
  include_directories("../source/lib/sqlite_orm-master/include")
  target_link_libraries (saper ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)
