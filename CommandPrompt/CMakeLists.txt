CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (CommandPrompt)

INCLUDE (SourceGroupByFolder)
INCLUDE (AutoIncludeDirectories)
INCLUDE (CopyDLLOnBuild)

LIST (APPEND SDL2_SEARCH_PATHS "${PROJECT_SOURCE_DIR}")

FIND_PACKAGE (SDL2 REQUIRED)
INCLUDE_DIRECTORIES ("${SDL2_INCLUDE_DIR}")

SET (CommandPrompt_HEADERS
	include/Core/Window.h
	include/Core/WindowSDL.h
	include/Events/Event.h
	include/Events/Event.inl
	include/EmbedResources/EmbedResource.h
	include/EmbedResources/FontConsola.h
	include/Utils/EasyBind.h)

SET (CommandPrompt_SOURCES
	src/Core/Window.cpp
	src/Core/WindowSDL.cpp)

SOURCE_GROUP_BY_FOLDER(CommandPrompt)
AUTO_INCLUDE_DIRECTORIES(CommandPrompt_HEADERS)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

ADD_LIBRARY (CommandPrompt_CoreLib ${CommandPrompt_SOURCES} ${CommandPrompt_HEADERS})

SOURCE_GROUP_BY_FOLDER(CommandPrompt)

ADD_EXECUTABLE (CommandPrompt src/main.cpp)
TARGET_LINK_LIBRARIES (CommandPrompt ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY} CommandPrompt_CoreLib)

IF (MSVC)
	SET (CommandPrompt_DLLS
		"${PROJECT_SOURCE_DIR}/lib/SDL2.dll")
		
	COPY_DLL_ON_BUILD (CommandPrompt "${CommandPrompt_DLLS}")
ENDIF (MSVC)

IF (COMMAND_PROMPT_BUILD_TESTS)
	ADD_SUBDIRECTORY (test)
ENDIF (COMMAND_PROMPT_BUILD_TESTS)