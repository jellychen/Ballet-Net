PROJECT(TestClient)
include_directories( "${PROJECT_SOURCE_DIR}/..")
include_directories( "${PROJECT_SOURCE_DIR}/../Ballet")
AUX_SOURCE_DIRECTORY(. srcs)
LINK_DIRECTORIES (
	"${PROJECT_SOURCE_DIR}/../Build/Ballet"
	"${PROJECT_SOURCE_DIR}/../Build/IniLoader"
	"${PROJECT_SOURCE_DIR}/../Build/LoTrace"
)
ADD_EXECUTABLE(TestClient ${srcs})
set (CMAKE_CXX_FLAGS "-fpermissive  ${CMAKE_CXX_FLAGS}")
TARGET_LINK_LIBRARIES(TestClient Ballet)
TARGET_LINK_LIBRARIES(TestClient IniLoader)
TARGET_LINK_LIBRARIES(TestClient LoTrace)
