# GLINT
cmake_minimum_required(VERSION 2.8) 

set(PATH_MINUIT_SRC ${CMAKE_SOURCE_DIR}/src/minuit)
set(PATH_LUSTRE ${CMAKE_SOURCE_DIR}/src/lustre)
set(PATH_MUD ${CMAKE_SOURCE_DIR}/src/mud)
set(PATH_LUA ${CMAKE_SOURCE_DIR}/src/mud/lune/luajit/src)

###############		 INCLUDES	#############################

include_directories(
	${PATH_MINUIT_SRC}
	${PATH_MINUIT_SRC}/src
	${PATH_MINUIT_SRC}/src/lib/brick
	${PATH_MINUIT_SRC}/src/lib/core
	${PATH_MINUIT_SRC}/src/lib/data
	${PATH_MINUIT_SRC}/src/lib/object
	${PATH_MINUIT_SRC}/src/lib/screen
	${PATH_MINUIT_SRC}/src/base
	${PATH_MINUIT_SRC}/src/app
	${PATH_MINUIT_SRC}/src/ops
	${PATH_MINUIT_SRC}/src/scene
	${PATH_MINUIT_SRC}/src/ctx
	${PATH_MINUIT_SRC}/src/draw
	${PATH_MINUIT_SRC}/src/ui
	${PATH_MINUIT_SRC}/src/umber

	${PATH_LUSTRE}
	${PATH_MUD}
	${PATH_LUA}
	)

project(Lud)

option(OPT_LUA_STATIC "Lua Static Lib" ON)
option(OPT_STUCCO_STATIC "Stucco static" ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Threads)
find_package(PNG REQUIRED)
find_library(JPG jpeg PATHS)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

add_subdirectory(src)

add_executable(
    lud
    src/lud.c
    src/lud_init.c
)

target_link_libraries(
		lud
		liblustre
		lualib
		lua_mud
		mud_static
		stdutil_static
		blenlib
		guardedalloc
		minuit-ctx 
		minuit-ops 
		minuit-ui 
		minuit-scene 
		minuit-lib_core
		minuit-lib_object
		minuit-lib_data
		minuit-lib_screen
		minuit-lib_brick
		minuit-draw 
		minuit-app 
		minuit-base
		dl #Lua
		readline #Lua
		)



list(APPEND LINK_FLAGS m)
list(APPEND LINK_FLAGS ${GLEW_LIBRARY})
list(APPEND LINK_FLAGS ${OPENGL_LIBRARIES})
list(APPEND LINK_FLAGS ${GLUT_LIBRARY})
list(APPEND LINK_FLAGS ${PNG_LIBRARY})
list(APPEND LINK_FLAGS ${JPG_LIBRARY})
list(APPEND LINK_FLAGS jpeg)
list(APPEND LINK_FLAGS ${LIB_OSC})
list(APPEND LINK_FLAGS pthread)

target_link_libraries(lud  ${LINK_FLAGS})


 
