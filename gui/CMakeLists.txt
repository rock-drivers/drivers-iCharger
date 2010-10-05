cmake_minimum_required(VERSION 2.6)

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)

INCLUDE(FindPkgConfig)
pkg_check_modules(IO REQUIRED "iodrivers_base")
INCLUDE_DIRECTORIES(. /usr/include/eigen2 ${IO_INCLUDE_DIRS} .)
LINK_DIRECTORIES(${IO_LIBRARY_DIRS} )

INCLUDE( ${QT_USE_FILE} )


set (CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	${CMAKE_HOME_DIRECTORY}
)


find_package(QWT5 REQUIRED)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_BINARY_DIR}
	${QT_INCLUDE_DIR}
	${QT_QT_INCLUDE_DIR}
	${QT_QTCORE_INCLUDE_DIR}
	${QT_QTGUI_INCLUDE_DIR}
	${QWT5_INCLUDE_DIR}
	.
)

qt4_automoc(iChargerGUI.cpp)
QT4_WRAP_CPP(MOC_SRCS iChargerGUI.hpp)
QT4_WRAP_UI(UIS_H iCharger.ui)


add_executable(iCharger
	main.cpp
	iChargerGUI.cpp
	../iCharger.cpp
	${MOC_SRCS}
	${UIS_H}
)


target_link_libraries(iCharger
	${QT_LIBRARIES} 
	${QWT5_LIBRARY}
	${IO_LIBRARIES}
)


#CONFIGURE_FILE(movementLib.pc.in movementLib.pc @ONLY)
#INSTALL(FILES 
#	${CMAKE_BINARY_DIR}/movementLib.pc 
#	DESTINATION lib/pkgconfig)
#
#
#INSTALL(TARGETS movementLib
#	RUNTIME DESTINATION bin
#	LIBRARY DESTINATION lib)

#INSTALL(FILES 
#	Movement.h
#	DESTINATION include
#)

