set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -D_GLIBCXX_USE_CXX11_ABI=0")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -g -O0 -fsanitize=address ")

# Configure to put executable in top level bin directory
#    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Build executable link to dependent libraries
    add_executable (perftest main.cpp)

