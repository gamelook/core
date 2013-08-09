project(core)

message("core start ...")

IF(WIN32)
	message("win32 preprocess ...")
	add_definitions(-DWIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DUSE_MEM_POOL)
ENDIF()

file(GLOB_RECURSE SOURCE_FILE "*.c*")
file(GLOB_RECURSE HEADER_FILE "*.h*")

IF(WIN32)
message("win32 path ...")
message($ENV{LIBEVENT_PATH})
INCLUDE_DIRECTORIES(
$ENV{LIBEVENT_PATH}/include
$ENV{LIBEVENT_PATH}/WIN32-Code
$ENV{LIBEVENT_PATH}/compat
$ENV{LUA_PATH}
$ENV{LOG_PATH}/include
$ENV{BOOST_PATH}
"."
)

LINK_DIRECTORIES(
$ENV{LIBEVENT_PATH}/lib
$ENV{LUA_PATH}
$ENV{CORE_PATH}
)

LINK_LIBRARIES(
libevent.lib
lua.lib
)

ELSE()

INCLUDE_DIRECTORIES(
/usr/local/include
.
)

LINK_DIRECTORIES(
/usr/local/lib
)

LINK_LIBRARIES(
event
lua
)

ENDIF()


ADD_LIBRARY(${PROJECT_NAME} ${SOURCE_FILE} ${HEADER_FILE})
TARGET_LINK_LIBRARIES(${PROJECT_NAME})
INSTALL(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION ${core_SOURCE_DIR}/../lib)
INSTALL(FILES ${HEADER_FILE} DESTINATION ${core_SOURCE_DIR}/../include/core)