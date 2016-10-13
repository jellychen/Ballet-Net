PROJECT(ZeusCollocation)
include_directories( "${PROJECT_SOURCE_DIR}/..")
include_directories( "${PROJECT_SOURCE_DIR}/../..")
include_directories( "${PROJECT_SOURCE_DIR}/../../Ballet")
AUX_SOURCE_DIRECTORY(. srcs)
LINK_DIRECTORIES (
	"${PROJECT_SOURCE_DIR}/../../Build/Ballet"
	"${PROJECT_SOURCE_DIR}/../../IniLoader"
	"${PROJECT_SOURCE_DIR}/../../Zeus/ZeusBase"
)
ADD_EXECUTABLE(ZeusCollocation ${srcs})
set (CMAKE_CXX_FLAGS "-fpermissive ${CMAKE_CXX_FLAGS}")
TARGET_LINK_LIBRARIES(ZeusCollocation Ballet)
TARGET_LINK_LIBRARIES(ZeusCollocation IniLoader)
TARGET_LINK_LIBRARIES(ZeusCollocation ZeusBase)
