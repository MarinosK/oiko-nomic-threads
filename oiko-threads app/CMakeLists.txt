#by Marinos Koutsomichalis, Heraklion 2015

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project("Oiko-nomic Threads")

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
set (SOURCES       src/helper.cpp
                   src/data.cpp
		   src/decoration.cpp
		   src/segment.cpp
		   src/controller.cpp
		   src/visualizer.cpp
		   lib/arduino-serial-lib
		   )
set (APP_SOURCES   src/oiko-threads.cpp		   
	           src/oikoThreadsApp.cpp)
set (TEST_SOURCES  src/tests.cpp
                   lib/gmock-all.cc
		   lib/gtest-all.cc)		 
include_directories(  /opt/local/include
		      /usr/local/include
		      /usr/local/include/gmock
		      /usr/local/include/gtest
		      lib
		      lib/ip
		      lib/osc
		      ) 
link_directories(     /opt/local/lib
		      # static_libs 
		      /usr/local/lib )
set(CMAKE_INSTALL_PREFIX  "${CMAKE_BINARY_DIR}/Install")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Install")

#find libraries
find_package(Boost 1.58.0 REQUIRED COMPONENTS chrono filesystem system)
find_package(OpenCV 3.0 REQUIRED)
if (OpenCV_FOUND)
    message( "-- OpenCV found")
endif()

include_directories(${Boost_INCLUDE_DIRS})
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
include_directories(${OpenCV_INCLUDE_DIRS})

#user configuration
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
  message("-- DEBUG MODE ON")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")
else()
  message("-- RELEASE MODE ON")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3")
endif()
option(EMULATION_MODE "Emulation mode is for demonstration only, no actual interaction with the machine takes place")
if(EMULATION_MODE)
  message("-- EMULATION_MODE ON")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DEMULATION_MODE")
else()
    message("-- EMULATION_MODE OFF")
endif()
option(DUAL_MODE "In Dual mode the software will also send stdout (but not stderr) through OSC (192.168.1.2:7000)")
if(DUAL_MODE)
  message("-- DUAL_MODE ON")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DDUAL_MODE")
  set(SOURCES ${SOURCES} lib\sendOsc.cpp)
  else()
    message("-- DUAL_MODE OFF")
endif()

# for dynamic linking comment out the following:
set(CMAKE_FIND_LIBRARY_SUFFIXES	".a")
set(BUILD_SHARED_LIBRARIES OFF)

# doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCUMENTATION)
  message("-- BUILD_DOCUMENTATION ON")
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
  endif()
  set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  configure_file(${doxyfile_in} ${doxyfile} @ONLY)
  
  add_custom_command( OUTPUT doc.lic #run tests
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile} && ln -s ${CMAKE_BINARY_DIR}/Install/docs/html/index.html ${CMAKE_BINARY_DIR}/Install/docs/index.html
    DEPENDS oiko-threads
    COMMENT "Generating documentation with Doxygen"
    VERBATIM )

  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Install/html DESTINATION  ${CMAKE_CURRENT_BINARY_DIR}/share/doc)

  add_custom_target( doc ALL DEPENDS doc.lic)
  
else()
  message("-- BUILD_DOCUMENTATION OFF")
endif()


# core
add_library(core ${SOURCES})
target_link_libraries(core ${OpenCV_LIBS})
target_link_libraries(core
  ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})


# configure and run tests		 
option(TEST_MODE "Compile and run tests" ON)
if(TEST_MODE)
      message("-- TEST_MODE ON")
add_executable(oiko-threads-test ${TEST_SOURCES})
target_link_libraries(oiko-threads-test pthread)
target_link_libraries(oiko-threads-test core)
add_custom_command( OUTPUT run_tests.lic #run tests
  COMMAND cd $<TARGET_FILE_DIR:oiko-threads> && ./oiko-threads-test && cd ${CMAKE_SOURCE_DIR} #need to change directory to get the correct path
  DEPENDS oiko-threads-test doc
  COMMENT "Running Tests"
  VERBATIM )
add_custom_target( RunTests ALL DEPENDS run_tests.lic)
else()
    message("-- TEST_MODE OFF")
endif()

# oiko-threads app
add_executable(oiko-threads ${APP_SOURCES})
target_link_libraries(oiko-threads core)
#target_link_libraries(oiko-threads ${OpenCV_LIBS})


add_custom_command(TARGET oiko-threads PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:oiko-threads>/data)

