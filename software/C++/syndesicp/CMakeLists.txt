cmake_minimum_required(VERSION 3.20)

project(syndesicp VERSION 0.1 DESCRIPTION "Syndesi communication protocol")

#include(GNUInstallDirs)

#file(GLOB LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
#file(GLOB LIB_HEADERS CONFIGURE_DEPENDS include/*.hpp)


#add_library(syndesicp SHARED ${LIB_SOURCES} ${LIB_HEADERS})
add_library(syndesicp SHARED
user_config/callbacks_configuration.hpp
include/core.hpp
include/frame.hpp
include/payloads.hpp
include/syndesi_tools.hpp
include/syndesi_types.hpp
include/syndesicp.hpp
include/callbacks.hpp
include/sdid.hpp
include/networkinterface.hpp
include/framemanager.cpp
src/core.cpp
src/frame.cpp
src/syndesi_tools.cpp
src/syndesi_types.cpp
src/sdid.cpp
src/networkinterface.cpp
src/framemanager.cpp
)

set_target_properties(syndesicp PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1 PUBLIC_HEADER include/syndesicp.hpp LIBRARY_OUTPUT_DIRECTORY build)

#configure_file(mylib.pc.in mylib.pc @ONLY)

target_include_directories(syndesicp PRIVATE src)
target_include_directories(syndesicp PRIVATE include)
target_include_directories(syndesicp PRIVATE user_config)

install(TARGETS syndesicp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    #PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)

#install(FILES ${CMAKE_BINARY_DIR}/syndesicp.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)