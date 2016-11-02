PROJECT(TestServer)
include_directories( "${PROJECT_SOURCE_DIR}/..")
include_directories( "${PROJECT_SOURCE_DIR}/../Ballet")
AUX_SOURCE_DIRECTORY(. srcs)
LINK_DIRECTORIES (
	"${PROJECT_SOURCE_DIR}/../Build/Ballet"
	"${PROJECT_SOURCE_DIR}/../Build/IniLoader"
	"${PROJECT_SOURCE_DIR}/../Build/LoTrace"
)
ADD_EXECUTABLE(TestServer ${srcs})
set (CMAKE_CXX_FLAGS "-fpermissive -O2 ${CMAKE_CXX_FLAGS}")
TARGET_LINK_LIBRARIES(TestServer Ballet)
TARGET_LINK_LIBRARIES(TestServer IniLoader)
TARGET_LINK_LIBRARIES(TestServer LoTrace)
