#
# Find the QWT libraries and include dir
#

# QWT5_INCLUDE_DIR  - Directories to include to use QWT
# QWT5_LIBRARY    - Files to link against to use QWT
# QWT5_FOUND        - When false, don't try to use QWT
#
# QWT5_DIR can be used to make it simpler to find the various include
# directories and compiled libraries when QWT was not installed in the
# usual/well-known directories (e.g. because you made an in tree-source
# compilation or because you installed it in an "unusual" directory).
# Just set QWT5_DIR it to your specific installation directory
#

FIND_PATH(QWT5_INCLUDE_DIR qwt.h
  PATHS
  ${QWT5_DIR}/include
  /usr/include/qwt5
  /usr/include/qwt-qt4
  /usr/include/qwt
  /usr/include
  /usr/local/include
)

FIND_LIBRARY( QWT5_LIBRARY qwt5 qwt qwt-qt4 
  PATHS
  /usr/lib
  /usr/local/lib
  ${QWT5_DIR}/lib
)

IF( QWT5_INCLUDE_DIR )
IF( QWT5_LIBRARY )
  FILE(READ ${QWT5_INCLUDE_DIR}/qwt_global.h _contents)
  STRING(REGEX MATCHALL "#define +QWT_VERSION +0x05[0-9]+" _match_str "${_contents}")
  STRING(REGEX REPLACE "#define +QWT_VERSION +0x(05[0-9]+)" "\\1" _match "${_match_str}")
  IF(${_match} GREATER 050000 OR ${_match} EQUAL 050000)
    SET( QWT5_FOUND "YES" )
    STRING(REGEX MATCHALL "#define +QWT_VERSION_STR +\".+\"" _version_str "${_contents}")
    STRING(REGEX REPLACE "#define +QWT_VERSION_STR +\"(.+)\"" "\\1" _version "${_version_str}")
    MESSAGE(STATUS "Found QWT Version ${_version}")

    MARK_AS_ADVANCED( QWT5_DIR )
    MARK_AS_ADVANCED( QWT5_INCLUDE_DIR )
    MARK_AS_ADVANCED( QWT5_LIBRARY )
  ENDIF(${_match} GREATER 050000 OR ${_match} EQUAL 050000)

ENDIF( QWT5_LIBRARY )
ENDIF( QWT5_INCLUDE_DIR )

IF( NOT QWT5_FOUND )
  MESSAGE("QWT installation was not found. Please provide QWT5_DIR:")
  MESSAGE("  - through the GUI when working with ccmake, ")
  MESSAGE("  - as a command line argument when working with cmake e.g. ")
  MESSAGE("    cmake .. -DQWT5_DIR:PATH=/usr/local/QWT-5.0.0 ")
  MESSAGE("Note: the following message is triggered by cmake on the first ")
  MESSAGE("    undefined necessary PATH variable (e.g. QWT5_INCLUDE_DIR).")
  MESSAGE("    Providing QWT5_DIR (as above described) is probably the")
  MESSAGE("    simplest solution unless you have a really customized/odd")
  MESSAGE("    QWT installation...")
  SET( QWT5_DIR "" CACHE PATH "Root of QWT instal tree." )
ENDIF( NOT QWT5_FOUND )

