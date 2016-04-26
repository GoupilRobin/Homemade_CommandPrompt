MACRO (COPY_DLL_ON_BUILD target dll_paths)
	IF (MSVC)
		ADD_CUSTOM_COMMAND (TARGET ${target}
							POST_BUILD
							COMMAND ${CMAKE_COMMAND} -E copy_if_different
							${dll_paths}
							$<TARGET_FILE_DIR:${target}>)
	ENDIF (MSVC)
ENDMACRO(COPY_DLL_ON_BUILD)