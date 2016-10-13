PROJECT(ZeusCollocation)
include_directories( "${PROJECT_SOURCE_DIR}/../..")
include_directories( "${PROJECT_SOURCE_DIR}/../../Ballet")
AUX_SOURCE_DIRECTORY(. srcs)
LINK_DIRECTORIES (
	"${PROJECT_SOURCE_DIR}/../../Build/Ballet"
	
)
ADD_EXECUTABLE(ZeusCollocation ${srcs})
set (CMAKE_CXX_FLAGS "-fpermissive ${CMAKE_CXX_FLAGS}")
TARGET_LINK_LIBRARIES(ZeusCollocation Ballet)
