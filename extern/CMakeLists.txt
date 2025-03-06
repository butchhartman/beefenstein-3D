cmake_minimum_required (VERSION 3.8)

include(FetchContent)

# ---------------------------------------------------
# CGLM

FetchContent_Declare(
	cglm

	GIT_REPOSITORY https://github.com/recp/cglm.git
)

FetchContent_GetProperties(cglm)
if (NOT cglm_POPULATED)
	FetchContent_Populate(cglm)
	add_subdirectory(
	${cglm_SOURCE_DIR} 
	${cglm_BINARY_DIR}
	EXCLUDE_FROM_ALL)
endif()