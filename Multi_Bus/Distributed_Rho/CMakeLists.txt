# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Set the output folder where your program will be created
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++0x")
#set(CMAKE_BINARY_DIR $/home/samie/code/Horizontal_Coordination_MILP_Dist_Mechanism_Design/glpk-4.65/examples/UC/cmake-3.11.1/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# Project's name
project(SerialCode)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
INCLUDE_DIRECTORIES($ENV{GUROBI_HOME}/include)
INCLUDE_DIRECTORIES(/home/samie/optmosek/mosek/7/tools/platform/linux64x86/h)

SET(GUROBI_LIB libgurobi65.so)
SET(MOSEK_LIB libmosek64.so)
# The following folder will be included
#include_directories("$/home/samie/code/Horizontal_Coordination_MILP_Dist_Mechanism_Design/glpk-4.65/examples/UC")
add_executable(
SerialCode
node.cpp 
generator.cpp 
load.cpp 
loadcont.cpp 
transl.cpp 
tlinecont.cpp 
network.cpp 
mainserialSCOPF.cpp 
gensolver.cpp
#gensolverOldCentralizedRho.cpp
)
TARGET_LINK_LIBRARIES(SerialCode $ENV{GUROBI_HOME}/lib/${GUROBI_LIB}  ${CMAKE_DL_LIBS})
TARGET_LINK_LIBRARIES(SerialCode /home/samie/optmosek/mosek/7/tools/platform/linux64x86/bin/${MOSEK_LIB}  ${CMAKE_DL_LIBS})
