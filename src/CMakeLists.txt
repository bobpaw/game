# Makefile stuff
include(FindPython3 OPTIONAL RESULT_VARIABLE HAS_FINDPYTHON3)
include_directories(.)
add_library(app OBJECT app.cc app.h)
target_compile_features(app PUBLIC cxx_auto_type $<IF:$<COMPILE_FEATURES:cxx_return_type_deduction>,cxx_return_type_deduction,cxx_trailing_return_types> cxx_noexcept cxx_nullptr cxx_decltype)
add_library(health_bar OBJECT health_bar.cc health_bar.h)
target_compile_features(health_bar PUBLIC cxx_noexcept cxx_uniform_initialization cxx_nullptr cxx_decltype)
target_include_directories(health_bar PUBLIC "${CURSES_INCLUDE_DIRS}")

if (HAS_FINDPYTHON3) # Don't bother if there's no FindPython3 file
find_package(Python3 COMPONENTS Interpreter)

# If Python3 is found, update itemlist.h. Otherwise, use whatever version exists already
if (Python3_Interpreter_FOUND)
add_custom_command(OUTPUT data/itemlist.h COMMAND "${Python3_EXECUTABLE}" ARGS "${PROJECT_SOURCE_DIR}/src/data/items.py" "--build" MAIN_DEPENDENCY data/items.json)
endif()
endif()

add_executable(game main.cc main.h app board.h item.h monster.h player.h data/itemlist.h correct_curses.h)
target_include_directories(game PRIVATE "${CURSES_INCLUDE_DIRS}")
target_compile_features(game PRIVATE cxx_lambdas cxx_decltype)
target_link_libraries(game "${CURSES_LIBRARIES}")
add_executable(battle battle.cc health_bar stats.h correct_curses.h)
target_compile_features(battle PRIVATE cxx_noexcept cxx_auto_type cxx_decltype)
target_include_directories(battle PRIVATE "${CURSES_INCLUDE_DIRS}")
target_link_libraries(battle "${CURSES_LIBRARIES}")

# Tests
add_executable(test_app EXCLUDE_FROM_ALL test_app.cc app correct_curses.h)
add_executable(test_board EXCLUDE_FROM_ALL test_board.cc board.h correc_curses.h
