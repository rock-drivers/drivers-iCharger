cmake_minimum_required(VERSION 2.6)


INCLUDE(FindPkgConfig)

pkg_check_modules(IO REQUIRED "iodrivers_base")
INCLUDE_DIRECTORIES(. /usr/include/eigen2 ${IO_INCLUDE_DIRS} .)
LINK_DIRECTORIES(${IO_LIBRARY_DIRS} )


add_executable(iCharger_test
	iCharger.cpp
	main.cpp
)

#add_library(iCharger SHARED
#	iCharger.cpp
#)

TARGET_LINK_LIBRARIES(iCharger_test
	${IO_LIBRARIES}
)

#TARGET_LINK_LIBRARIES(iCharger
#	${IO_LIBRARIES}
#)

#INSTALL(TARGETS iCharger 
#	LIBRARY DESTINATION lib
#)


INSTALL(FILES iCharger.h DESTINATION include)


add_subdirectory(gui)

#CONFIGURE_FILE(igc.pc.in igc.pc @ONLY)
#INSTALL(FILES 
#	${CMAKE_BINARY_DIR}/igc.pc 
#	DESTINATION lib/pkgconfig
#)


