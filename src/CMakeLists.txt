add_library(tube Tube.cpp Tube.h "State.cpp")
target_include_directories(tube PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})