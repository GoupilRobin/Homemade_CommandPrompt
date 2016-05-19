CMAKE_MINIMUM_REQUIRED (VERSION 3.5 FATAL_ERROR)
PROJECT (CommandPrompt CXX)

INCLUDE (SourceGroupByFolder)
INCLUDE (AutoIncludeDirectories)
INCLUDE (CopyDLLOnBuild)

LIST (APPEND SDL2_SEARCH_PATHS "${PROJECT_SOURCE_DIR}")
LIST (APPEND SDL2TTF_SEARCH_PATHS "${PROJECT_SOURCE_DIR}")
LIST (APPEND SDL2_SEARCH_PATHS "${PROJECT_SOURCE_DIR}")

FIND_PACKAGE (SDL2 REQUIRED)
INCLUDE_DIRECTORIES ("${SDL2_INCLUDE_DIR}")
FIND_PACKAGE (SDL2TTF REQUIRED)
INCLUDE_DIRECTORIES ("${SDL2TTF_INCLUDE_DIR}")
FIND_PACKAGE (GLM REQUIRED)
INCLUDE_DIRECTORIES ("${GLM_INCLUDE_DIR}")

SET (CommandPrompt_HEADERS
	include/Core/Rendering/Window.h
	include/Core/Rendering/WindowSDL.h
	include/Core/Rendering/Renderer.h
	include/Core/Rendering/RendererSDL.h
	include/Core/Rendering/Drawable.h
	include/Core/Rendering/Font.h
	include/Core/Rendering/FontSDL.h
	include/Core/Rendering/Text.h
	include/Core/Rendering/TextSDL.h
	include/Core/Rendering/TextLineSDL.h
	include/Core/General/Color.h
	include/Events/Event.h
	include/Events/Event.inl
	include/EmbedResources/EmbedResource.h
	include/EmbedResources/FontConsola.h
	include/Utils/EasyBind.h
	include/Utils/ustring.h
	include/Utils/VariableMonitor.h
	include/Utils/VariableMonitor.inl
	include/Utils/RingBuffer.h
	include/Utils/RingBuffer.inl
	include/Utils/TerminalBuffer.h
	include/Utils/TerminalBuffer.inl
	include/Game/Terminal.h)

SET (CommandPrompt_SOURCES
	src/Core/Rendering/WindowSDL.cpp
	src/Core/Rendering/RendererSDL.cpp
	src/Core/Rendering/FontSDL.cpp
	src/Core/Rendering/TextSDL.cpp
	src/Core/Rendering/TextLineSDL.cpp
	src/Core/General/Color.cpp
	src/Game/Terminal.cpp)

SOURCE_GROUP_BY_FOLDER(CommandPrompt)
AUTO_INCLUDE_DIRECTORIES(CommandPrompt_HEADERS)

SET (PROJECT_CXX_FEATURES
	"cxx_variadic_templates"
	"cxx_generic_lambdas"
	"cxx_lambdas"
	"cxx_lambda_init_captures")

ADD_LIBRARY (CommandPrompt_CoreLib ${CommandPrompt_SOURCES} ${CommandPrompt_HEADERS})

SOURCE_GROUP_BY_FOLDER(CommandPrompt)

ADD_EXECUTABLE (CommandPrompt src/main.cpp)
TARGET_LINK_LIBRARIES (CommandPrompt ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY} ${SDL2TTF_LIBRARY} CommandPrompt_CoreLib)
TARGET_COMPILE_FEATURES(CommandPrompt PUBLIC ${PROJECT_CXX_FEATURES})

IF (MSVC)
	SET (CommandPrompt_DLLS
		"${PROJECT_SOURCE_DIR}/lib/SDL2.dll"
		"${PROJECT_SOURCE_DIR}/lib/SDL2_ttf.dll")
		
	COPY_DLL_ON_BUILD (CommandPrompt "${CommandPrompt_DLLS}")
ENDIF (MSVC)

IF (COMMAND_PROMPT_BUILD_TESTS)
	ADD_SUBDIRECTORY (test)
ENDIF (COMMAND_PROMPT_BUILD_TESTS)