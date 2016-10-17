PROJECT(ZeusBroker)
include_directories( "${PROJECT_SOURCE_DIR}/..")
include_directories( "${PROJECT_SOURCE_DIR}/../..")
include_directories( "${PROJECT_SOURCE_DIR}/../../Ballet")
AUX_SOURCE_DIRECTORY(. srcs)
LINK_DIRECTORIES (
	"${PROJECT_SOURCE_DIR}/../../Build/Ballet"
	"${PROJECT_SOURCE_DIR}/../../IniLoader"
	"${PROJECT_SOURCE_DIR}/../../Zeus/ZeusBase"
)
ADD_EXECUTABLE(ZeusBroker ${srcs})
set (CMAKE_CXX_FLAGS "-fpermissive -O2 ${CMAKE_CXX_FLAGS}")
TARGET_LINK_LIBRARIES(ZeusBroker Ballet)
TARGET_LINK_LIBRARIES(ZeusBroker IniLoader)
TARGET_LINK_LIBRARIES(ZeusBroker ZeusBase)
