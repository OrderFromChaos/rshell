CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

# Used for compilation with the -g flag; needed for useful gdb
# SET(DEBUG_FLAG "-g")
# add_definitions(${DEBUG_FLAG})

SET(C11 "-std=c++11")
add_definitions(${C11})

SET(warnings "-Wall")
add_definitions(${warnings})

FILE(GLOB MyTokens header/tokens/*.cpp)
FILE(GLOB MyHeaders header/*.cpp)

ADD_EXECUTABLE(rshell
    header/rshellutils.cpp
    header/rshellclass.cpp
    src/rshell.cpp
)

# ADD_EXECUTABLE(sandbox
#     src/sandbox.cpp
# )

# ADD_EXECUTABLE(test
# 	  test.cpp
#     header/rshellclass.cpp
#     ${MyTokens}
# )

# TARGET_LINK_LIBRARIES(test gtest)
# TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
