set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

cmake_minimum_required(VERSION 3.20)

project(syndesicp_communication VERSION 0.1)

include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
  set(CTEST_BUILD_FLAGS -j${N})
  set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${N})
endif()

# Only run to copy new config files from the syndesicp library (will erase the current configuration)
#file(COPY ../../Syndesi/software/C++/syndesicp/user_config DESTINATION syndesicp)

#add_subdirectory(syndesicp)
include_directories(../../software/C++/syndesicp/include)
include_directories(user_config)

#file(GLOB USER_CONFIG_HEADERS CONFIGURE_DEPENDS user_config/*.hpp)
#add_library(user_config ${USER_CONFIG_HEADERS})


file(GLOB LIB_SOURCES CONFIGURE_DEPENDS ../../software/C++/syndesicp/src/*.cpp)
file(GLOB LIB_HEADERS CONFIGURE_DEPENDS ../../software/C++/syndesicp/include/*.hpp)


add_library(syndesicp_device ${LIB_SOURCES} ${LIB_HEADERS})
target_compile_definitions(syndesicp_device PUBLIC -DDEVICE_MODE=1)

add_library(syndesicp_host ${LIB_SOURCES} ${LIB_HEADERS})
target_compile_definitions(syndesicp_host PUBLIC -DHOST_MODE=1)

add_executable(host host/host.cpp)
set_target_properties(host PROPERTIES RUNTIME_OUTPUT_DIRECTORY host)
target_link_libraries(host syndesicp_host)
target_compile_features(host PRIVATE cxx_std_17)

add_executable(device device/device.cpp)
set_target_properties(device PROPERTIES RUNTIME_OUTPUT_DIRECTORY device)
target_link_libraries(device syndesicp_device)
target_compile_features(device PRIVATE cxx_std_17)


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()