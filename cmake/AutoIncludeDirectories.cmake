MACRO (AUTO_INCLUDE_DIRECTORIES files)
	FOREACH (file ${${files}})
	    file (RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}/" "${PROJECT_SOURCE_DIR}/${file}")
	    GET_FILENAME_COMPONENT (dir "${relative_file}" PATH)
		INCLUDE_DIRECTORIES ("${dir}")
	ENDFOREACH (file)
ENDMACRO (AUTO_INCLUDE_DIRECTORIES)