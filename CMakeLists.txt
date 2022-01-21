cmake_minimum_required(VERSION 3.10)

#set the project name
project(Test LANGUAGES C CXX)
set(my_sourceFiles ${PROJECT_SOURCE_DIR}/source/main.cpp)
set(GDP_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(exe ${my_sourceFiles})

message(STATUS "CMAKE_C_COMPILER = ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}")

message("*** MPI ***")
if(NOT MPI_DISABLE)
        find_package(MPI)
  if(MPI_C_FOUND OR MPI_CXX_FOUND)
    message(STATUS "MPI_C_FOUND = ${MPI_C_FOUND}" )
    message(STATUS "MPI_C_INCLUDE_PATH = ${MPI_C_INCLUDE_PATH}" )
    message(STATUS "MPI_C_LIBRARIES = ${MPI_C_LIBRARIES}" )
    message(STATUS "MPI_C_COMPILE_FLAGS = ${MPI_C_COMPILE_FLAGS}" )
    message(STATUS "MPI_CXX_FOUND = ${MPI_CXX_FOUND}" )
    message(STATUS "MPI_CXX_INCLUDE_PATH = ${MPI_CXX_INCLUDE_PATH}" )
    message(STATUS "MPI_CXX_LIBRARIES = ${MPI_CXX_LIBRARIES}" )
    message(STATUS "MPI_CXX_COMPILE_FLAGS = ${MPI_CXX_COMPILE_FLAGS}" )
    # compile with MPI if found
    if(MPI_C_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MPI_C_COMPILE_FLAGS}")
        set(GDP_INCLUDE_DIRS ${GDP_INCLUDE_DIRS} ${MPI_C_INCLUDE_PATH})
        set(MPI_LIBRARIES ${MPI_LIBRARIES} ${MPI_C_LIBRARIES})
    endif(MPI_C_FOUND)
    if(MPI_CXX_FOUND)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_COMPILE_FLAGS}")
        set(GDP_INCLUDE_DIRS ${GDP_INCLUDE_DIRS} ${MPI_CXX_INCLUDE_PATH})
        set(MPI_LIBRARIES ${MPI_LIBRARIES} ${MPI_CXX_LIBRARIES})
    endif(MPI_CXX_FOUND)
  else(MPI_C_FOUND OR MPI_CXX_FOUND)
    message(STATUS "${Red}MPI not found${ColourReset}")
  endif(MPI_C_FOUND OR MPI_CXX_FOUND)
endif(NOT MPI_DISABLE)
message("")

target_link_libraries(
        exe
        ${MPI_LIBRARIES}
)

set_target_properties(
        exe
        PROPERTIES
        INCLUDE_DIRECTORIES "${GDP_INCLUDE_DIRS}"
        #COMPILE_DEFINITIONS "${GDP_COMPILE_DEFINITIONS}"
        #COMPILE_FLAGS "${GDP_COMPILE_FLAGS}"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
        OUTPUT_NAME "exe"
)
