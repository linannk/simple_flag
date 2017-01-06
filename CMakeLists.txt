cmake_minimum_required (VERSION 2.8)
project (simple_flags)

set (CMAKE_CXX_FLAGS "-std=c++11")
set (CMAKE_C_FLAGS "-std=c11")

source_group (include FILES simple_flags.h)
source_group (src FILES simple_flags.cpp)
set (simple_flags_SRC simple_flags.cpp simple_flags.h)

add_library (simple_flags STATIC ${simple_flags_SRC})

#if (EXISTS test/CMakeLists.txt)
	add_subdirectory (test)
#endif()
