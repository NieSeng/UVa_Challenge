# CMakeList.txt : CMake project for UVa_Challenge, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (UVa_00118 "UVa_00118.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UVa_00118 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
