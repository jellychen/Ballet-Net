PROJECT(Test)
include_directories( "${PROJECT_SOURCE_DIR}/..")
AUX_SOURCE_DIRECTORY(. srcs)
LINK_DIRECTORIES (
	"${PROJECT_SOURCE_DIR}/../Build/Ballet"
	"${PROJECT_SOURCE_DIR}/../Build/Ballet/Common"
	"${PROJECT_SOURCE_DIR}/../Build/Ballet/BootUtil"
	"${PROJECT_SOURCE_DIR}/../Build/Ballet/Network"
)
ADD_EXECUTABLE(Test ${srcs})
set (CMAKE_CXX_FLAGS "-fpermissive ${CMAKE_CXX_FLAGS}")
TARGET_LINK_LIBRARIES(Test Ballet)
