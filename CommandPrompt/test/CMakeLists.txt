CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (CommandPrompt_Test)
ENABLE_TESTING ()

INCLUDE (SourceGroupByFolder)
INCLUDE (AutoIncludeDirectories)
INCLUDE (CopyDLLOnBuild)

SET (GTEST_ROOT "${PROJECT_SOURCE_DIR}")

FIND_PACKAGE (SDL2 REQUIRED)
INCLUDE_DIRECTORIES ("${SDL2_INCLUDE_DIR}")
FIND_PACKAGE (GTest REQUIRED)
INCLUDE_DIRECTORIES ("${GTEST_INCLUDE_DIRS}")

SET (CommandPrompt_Test_HEADERS
	include/Test_Event.h)

SET (CommandPrompt_Test_SOURCES
	src/main.cpp
	src/Test_Event.cpp)

SOURCE_GROUP_BY_FOLDER(CommandPrompt_Test)
AUTO_INCLUDE_DIRECTORIES(CommandPrompt_Test_HEADERS)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

ADD_EXECUTABLE (CommandPrompt_Test ${CommandPrompt_Test_SOURCES} ${CommandPrompt_Test_HEADERS})
TARGET_LINK_LIBRARIES (CommandPrompt_Test ${SDL2_LIBRARY} CommandPrompt_CoreLib ${GTEST_LIBRARIES})

IF (MSVC)
	SET (CommandPrompt_Test_DLLS
		"${CommandPrompt_DLLS}"
		"${PROJECT_SOURCE_DIR}/lib/gtest.dll")
	COPY_DLL_ON_BUILD (CommandPrompt_Test "${CommandPrompt_Test_DLLS}")
ENDIF (MSVC)

add_test(CommandPromptTest CommandPrompt_Test)