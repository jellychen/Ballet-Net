PROJECT(IniLoader)
include_directories("${PROJECT_SOURCE_DIR}")
AUX_SOURCE_DIRECTORY(. dir_srcs)
set (CMAKE_CXX_FLAGS "-fpermissive -O2 ${CMAKE_CXX_FLAGS}")
ADD_LIBRARY(IniLoader STATIC ${dir_srcs})
