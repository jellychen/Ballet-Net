PROJECT(ZeusBase)
include_directories( "${PROJECT_SOURCE_DIR}/..")
include_directories( "${PROJECT_SOURCE_DIR}/../..")
include_directories( "${PROJECT_SOURCE_DIR}/../../Ballet")
AUX_SOURCE_DIRECTORY(. srcs)
LINK_DIRECTORIES (
	"${PROJECT_SOURCE_DIR}/../../Build/Ballet"
	"${PROJECT_SOURCE_DIR}/../../IniLoader"
	"${PROJECT_SOURCE_DIR}/../../Zeus/ZeusBase"
)
AUX_SOURCE_DIRECTORY(. dir_srcs)
set (CMAKE_CXX_FLAGS "-fpermissive -O2 ${CMAKE_CXX_FLAGS}")
ADD_LIBRARY(ZeusBase STATIC ${dir_srcs})
