set (simple_flags_INCLUDE_DIR ${PROJECT_SOURCE_DIR})
include_directories (${simple_flags_INCLUDE_DIR})
add_executable (test_simple_flags main.cpp)
target_link_libraries(test_simple_flags simple_flags)
