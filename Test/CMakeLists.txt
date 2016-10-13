PROJECT(Test)
include_directories( "${PROJECT_SOURCE_DIR}/..")
include_directories( "${PROJECT_SOURCE_DIR}/../Ballet")
AUX_SOURCE_DIRECTORY(. srcs)
LINK_DIRECTORIES (
	"${PROJECT_SOURCE_DIR}/../Build/Ballet"
	"${PROJECT_SOURCE_DIR}/../IniLoader"
)
ADD_EXECUTABLE(Test ${srcs})
set (CMAKE_CXX_FLAGS "-fpermissive ${CMAKE_CXX_FLAGS}")
TARGET_LINK_LIBRARIES(Test Ballet)
TARGET_LINK_LIBRARIES(Test IniLoader)
