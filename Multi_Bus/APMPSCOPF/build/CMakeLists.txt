# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8.7)

# Set the output folder where your program will be created
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++0x")
#set(CMAKE_BINARY_DIR $/home/samie/code/Horizontal_Coordination_MILP_Dist_Mechanism_Design/glpk-4.65/examples/UC/cmake-3.11.1/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# Project's name
project(SerialCode)
INCLUDE_DIRECTORIES($ENV{GUROBI_HOME}/include)
SET(GUR_LIB libgurobi90.so)
SET(GUR_LIBR libgurobi_c++.a)
SET(GUR_LIBRA libgurobi_g++5.2.a)
# The following folder will be included
#include_directories("$/home/samie/code/Horizontal_Coordination_MILP_Dist_Mechanism_Design/glpk-4.65/examples/UC")
add_executable(
SerialCode
/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/code/node.cpp 
/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/code/generator.cpp 
/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/code/load.cpp 
/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/code/transl.cpp 
/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/code/network.cpp 
/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/code/maintwoserialLASCOPF.cpp 
/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/code/gensolverBase.cpp
/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/code/gensolverCont.cpp
)
TARGET_LINK_LIBRARIES(SerialCode /home/samie/opt/gurobi900/linux64/lib/${GUR_LIBR};/home/samie/opt/gurobi900/linux64/lib/${GUR_LIBRA};/home/samie/opt/gurobi900/linux64/lib/${GUR_LIB}  ${CMAKE_DL_LIBS})
